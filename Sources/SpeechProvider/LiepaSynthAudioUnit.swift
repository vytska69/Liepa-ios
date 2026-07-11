import AVFoundation
import LiepaCore

/// The LIEPA Lithuanian unit-selection synthesiser exposed to the system (and
/// thus VoiceOver) as an `AVSpeechSynthesisProviderAudioUnit`.
///
/// Audio is produced at the engine's native 22050 Hz, 16-bit mono, converted to
/// the Float32 format the host expects and vended through the render block.
public final class LiepaSynthAudioUnit: AVSpeechSynthesisProviderAudioUnit {

    private let appGroup = "group.lt.liepa.tts"

    private var outputBus: AUAudioUnitBus
    private var _outputBusses: AUAudioUnitBusArray!
    private let format: AVAudioFormat

    // Synthesised audio, normalised Float32, guarded by `mutex`.
    private var output: [Float32] = []
    private var outputOffset = 0
    private let mutex = DispatchSemaphore(value: 1)

    private var engine: LiepaSynth?

    @objc override init(componentDescription: AudioComponentDescription,
                        options: AudioComponentInstantiationOptions) throws {
        var asbd = AudioStreamBasicDescription(
            mSampleRate: LiepaSynth.sampleRate,
            mFormatID: kAudioFormatLinearPCM,
            mFormatFlags: kAudioFormatFlagsNativeFloatPacked | kAudioFormatFlagIsNonInterleaved,
            mBytesPerPacket: 4, mFramesPerPacket: 1, mBytesPerFrame: 4,
            mChannelsPerFrame: 1, mBitsPerChannel: 32, mReserved: 0)
        format = AVAudioFormat(cmAudioFormatDescription:
            try! CMAudioFormatDescription(audioStreamBasicDescription: asbd))
        outputBus = try AUAudioUnitBus(format: format)
        try super.init(componentDescription: componentDescription, options: options)
        _outputBusses = AUAudioUnitBusArray(audioUnit: self, busType: .output, busses: [outputBus])
    }

    public override var outputBusses: AUAudioUnitBusArray { _outputBusses }

    // MARK: Voices

    public override var speechVoices: [AVSpeechSynthesisProviderVoice] {
        get {
            let installed = VoiceManager.installedVoices()
            let voices = installed.isEmpty ? [LiepaVoice.regina, .edvardas] : installed
            return voices.map { v in
                let voice = AVSpeechSynthesisProviderVoice(
                    name: v.displayName,
                    identifier: "lt.liepa.\(v.folderName.lowercased())",
                    primaryLanguages: ["lt-LT"],
                    supportedLanguages: ["lt-LT"])
                voice.gender = (v == .regina || v == .aiste) ? .female : .male
                return voice
            }
        }
        set {}
    }

    // MARK: Synthesis

    public override func synthesizeSpeechRequest(_ request: AVSpeechSynthesisProviderRequest) {
        let ssml = request.ssmlRepresentation
        var text = Self.plainText(fromSSML: ssml)
        // VoiceOver announces a capital as "didžioji raidė: X"; the colon in that
        // fixed phrase must not be spoken as "dvitaškis" (typing a real colon still
        // is, since that arrives as a lone ":").
        text = text.replacingOccurrences(of: "raidė\\s*:", with: "raidė",
                                         options: [.regularExpression, .caseInsensitive])
        var voice = Self.voice(for: request.voice.identifier)
        if !VoiceManager.isInstalled(voice) {
            voice = VoiceManager.installedVoices().first ?? voice
        }
        var modes = currentModes()
        // VoiceOver character feedback (typing, swiping keyboard keys, deleting a
        // symbol) sends single characters. Force full punctuation so the engine
        // names ?, , . ; etc. regardless of the user's Skyryba setting, and for the
        // few symbols the engine cannot name (-, •, …, →, ≠ …) substitute a name.
        if text.count == 1
            || ssml.range(of: "interpret-as=\"characters\"", options: .caseInsensitive) != nil {
            modes.punctuation = .all
            if text.count == 1, let ch = text.first, let name = Self.symbolNames[ch] {
                text = name
            }
        }
        let (desired, tonas) = Self.prosody(fromSSML: ssml)
        // The engine floors at greitis 30. For anything faster (the top of
        // VoiceOver's rate slider), keep the engine at 30 and time-compress the
        // rest with SOLA — the engine stays byte-identical.
        var greitis = desired
        var olaFactor = 1.0
        if desired < 30 {
            olaFactor = 30.0 / Double(max(desired, 1))
            greitis = 30
        }

        do {
            try ensureEngine(for: voice)
            let pcm = try engine!.synthesize(text, greitis: greitis, tonas: tonas, modes: modes)
            let samples = olaFactor > 1.0001
                ? Self.timeCompress(pcm.samples, factor: olaFactor) : pcm.samples
            let volume = Self.volumeFactor(fromSSML: ssml)
            let floats = samples.map { max(-1, min(1, Float32($0) / 32767.0 * volume)) }
            mutex.wait()
            output = floats
            outputOffset = 0
            mutex.signal()
        } catch {
            mutex.wait(); output = []; outputOffset = 0; mutex.signal()
        }
    }

    public override func cancelSpeechRequest() {
        mutex.wait(); output.removeAll(); outputOffset = 0; mutex.signal()
    }

    public override var internalRenderBlock: AUInternalRenderBlock {
        { [weak self] actionFlags, _, frameCount, _, outputData, _, _ in
            guard let self else { return kAudioUnitErr_NoConnection }
            let abl = UnsafeMutableAudioBufferListPointer(outputData)
            guard let raw = abl[0].mData else { return noErr }
            let frames = raw.assumingMemoryBound(to: Float32.self)
            frames.update(repeating: 0, count: Int(frameCount))

            self.mutex.wait()
            let count = min(self.output.count - self.outputOffset, Int(frameCount))
            if count > 0 {
                self.output.withUnsafeBufferPointer { p in
                    frames.update(from: p.baseAddress!.advanced(by: self.outputOffset), count: count)
                }
                self.outputOffset += count
            }
            abl[0].mDataByteSize = UInt32(count * MemoryLayout<Float32>.size)
            if self.outputOffset >= self.output.count {
                actionFlags.pointee = .offlineUnitRenderAction_Complete
                self.output.removeAll(keepingCapacity: true)
                self.outputOffset = 0
            }
            self.mutex.signal()
            return noErr
        }
    }

    // MARK: Helpers

    private func ensureEngine(for voice: LiepaVoice) throws {
        if let engine = engine {
            if engine.loadedVoice == voice { return }
            // The LithUSS engine can load only one voice per process and cannot
            // switch (initLUSS crashes on re-init). Relaunch so the next request
            // loads the newly selected voice.
            exit(0)
        }
        guard let path = VoiceManager.dataParentPath() else {
            throw NSError(domain: "Liepa", code: 1,
                          userInfo: [NSLocalizedDescriptionKey: "liepa-data not found"])
        }
        engine = try LiepaSynth(dataParentPath: path, voice: voice)
    }

    /// Time-compress (speed up) mono 16-bit PCM by `factor` (>1 = faster) using
    /// SOLA — synchronized overlap-add — which shortens duration while keeping
    /// pitch. Extends speech rate beyond the engine's own greitis=30 floor.
    static func timeCompress(_ input: [Int16], factor: Double) -> [Int16] {
        guard factor > 1.0001, input.count > 4096 else { return input }
        let x = input.map { Float($0) }
        let n = x.count
        let blockLen = 512                                  // ~23 ms @ 22050 Hz
        let overlap = 256                                   // 50 % overlap / synthesis hop
        let analysisHop = Int((Double(overlap) * factor).rounded())
        let kMax = 128                                      // ± alignment search

        var y = [Float]()
        y.reserveCapacity(Int(Double(n) / factor) + blockLen)
        y.append(contentsOf: x[0..<blockLen])

        var m = 1
        while true {
            let analysis = m * analysisHop
            if analysis + kMax + blockLen > n { break }
            let ovStart = y.count - overlap

            // Pick the shift that best aligns the incoming block with the tail.
            var bestK = 0
            var bestCorr = -Float.greatestFiniteMagnitude
            var k = max(-kMax, -analysis)
            while k <= kMax {
                var corr: Float = 0
                var i = 0
                while i < overlap {
                    corr += y[ovStart + i] * x[analysis + k + i]
                    i += 2
                }
                if corr > bestCorr { bestCorr = corr; bestK = k }
                k += 1
            }
            let src = analysis + bestK

            // Linear crossfade over the overlap, then append the block remainder.
            for i in 0..<overlap {
                let w = Float(i) / Float(overlap)
                y[ovStart + i] = y[ovStart + i] * (1 - w) + x[src + i] * w
            }
            y.append(contentsOf: x[(src + overlap)..<(src + blockLen)])
            m += 1
        }
        return y.map { Int16(max(-32768, min(32767, $0.rounded()))) }
    }

    private static func voice(for identifier: String) -> LiepaVoice {
        let id = identifier.lowercased()
        return LiepaVoice.allCases.first { id.contains($0.folderName.lowercased()) } ?? .regina
    }

    private func currentModes() -> LiepaModes {
        let d = UserDefaults(suiteName: appGroup) ?? .standard
        func flag(_ key: String, _ def: Bool) -> Bool {
            d.object(forKey: key) == nil ? def : d.bool(forKey: key)
        }
        func level(_ key: String, _ def: Int) -> Int {
            d.object(forKey: key) == nil ? def : d.integer(forKey: key)
        }
        return LiepaModes(
            abbreviations: flag("lith_tts_santrumpos", true),
            numbers: LiepaNumbers(rawValue: level("lith_tts_skaiciai", 4)) ?? .normal,
            punctuation: LiepaPunctuation(rawValue: level("lith_tts_skyryba", 1)) ?? .off,
            emoji: flag("lith_tts_emoji", false))
    }

    /// Extract VoiceOver's prosody from the request SSML and map it to the
    /// engine's `greitis` (15…300, 100 = normal, higher = slower) and `tonas`
    /// (100 = normal, higher = higher). `<prosody rate="N%" pitch="N%">` 100% = neutral.
    static func prosody(fromSSML ssml: String) -> (greitis: Int32, tonas: Int32) {
        // Returns a value normalised so that 100 == "neutral", regardless of
        // whether the SSML expresses it as a percentage ("110%"), a relative
        // change ("+10%"/"-10%") or a bare multiplier ("1.1").
        func neutral100(_ attr: String) -> Float? {
            guard let r = ssml.range(of: "\(attr)=\"", options: .caseInsensitive) else { return nil }
            let tail = ssml[r.upperBound...]
            guard let end = tail.firstIndex(of: "\"") else { return nil }
            var raw = String(tail[tail.startIndex..<end]).trimmingCharacters(in: .whitespaces)
            let relative = raw.hasPrefix("+") || raw.hasPrefix("-")
            let isPercent = raw.contains("%")
            raw = raw.replacingOccurrences(of: "%", with: "")
            guard let v = Float(raw) else { return nil }
            if relative { return 100 + v }            // "+10%" -> 110
            if isPercent { return v }                 // "110%" -> 110
            return v < 10 ? v * 100 : v               // "1.1" -> 110, "110" -> 110
        }
        // `greitis` is a *lengthening* percentage (100 = normal, higher = slower);
        // the system's prosody rate is the opposite, so map inversely.
        // Faithful up to normal (rate 100% → greitis 100). Above normal, ramp
        // harder (power curve) so the top of VoiceOver's rate slider asks for a
        // "desired" greitis down to ~10 (~3× faster). The engine itself floors at
        // 30; the caller time-compresses the sub-30 remainder with SOLA. Slow
        // half unchanged.
        let pr = max(neutral100("rate") ?? 100, 1)
        let g = pr <= 100 ? 10000.0 / pr : 100.0 * pow(100.0 / pr, 1.7)
        let greitis = Int32(min(max(g, 10), 300))              // 100→100, 200→31, 400→10(clamp)
        // `tonas` maps directly from pitch% (higher = higher pitch).
        let tonas = Int32(min(max(neutral100("pitch") ?? 100, 50), 300))
        return (greitis, tonas)
    }

    /// VoiceOver's speech volume from `<prosody volume="…">` as a 0…1 gain
    /// (the engine has no volume control, so we scale the samples ourselves).
    static func volumeFactor(fromSSML ssml: String) -> Float {
        guard let r = ssml.range(of: "volume=\"", options: .caseInsensitive) else { return 1 }
        let tail = ssml[r.upperBound...]
        guard let end = tail.firstIndex(of: "\"") else { return 1 }
        let raw = String(tail[tail.startIndex..<end]).trimmingCharacters(in: .whitespaces)
        let low = raw.lowercased()
        switch low {
        case "silent":         return 0
        case "x-soft":         return 0.3
        case "soft":           return 0.55
        case "medium":         return 0.75
        case "loud", "x-loud": return 1
        default: break
        }
        // VoiceOver expresses volume in decibels, e.g. volume="-3.741733dB"
        // (0 dB = full, negative = quieter). Convert to a linear amplitude gain.
        if low.hasSuffix("db") {
            let num = low.dropLast(2).trimmingCharacters(in: .whitespaces)
            guard let db = Float(num) else { return 1 }
            return min(max(pow(10, db / 20), 0), 1)
        }
        let relative = raw.hasPrefix("+") || raw.hasPrefix("-")
        let pctStr = raw.replacingOccurrences(of: "%", with: "")
        guard let v = Float(pctStr) else { return 1 }
        let pct = relative ? 100 + v : (v <= 1 ? v * 100 : v)   // "0.5"→50, "50"→50, "+10"→110
        return min(max(pct / 100, 0), 1)
    }

    /// Lithuanian names for single symbols the LithUSS engine cannot voice on its
    /// own (used only for VoiceOver character feedback). Everything the engine can
    /// name is left to the engine.
    static let symbolNames: [Character: String] = [
        "-": "brūkšnys", "—": "brūkšnys", "–": "brūkšnys", "•": "punktas",
        "…": "daugtaškis", "‰": "promilė", "’": "apostrofas", "‘": "apostrofas",
        "‚": "kablelis", "‹": "kampinė kabutė", "›": "kampinė kabutė",
        "№": "numeris", "™": "prekės ženklas", "′": "štrichas", "″": "dvigubas štrichas",
        "·": "taškas", "†": "kryželis", "¡": "apverstas šauktukas", "¿": "apverstas klaustukas",
        "→": "rodyklė", "←": "rodyklė kairėn", "↑": "rodyklė aukštyn", "↓": "rodyklė žemyn",
        "≠": "nelygu", "≤": "mažiau arba lygu", "≥": "daugiau arba lygu",
        "∑": "suma", "√": "kvadratinė šaknis", "∞": "begalybė", "≈": "apytiksliai lygu",
        "π": "pi", "₽": "rublis",
    ]

    static func plainText(fromSSML ssml: String) -> String {
        // The LithUSS engine cannot parse SSML, so preserve the separation the
        // tags express: <break> → a phrase pause, any other tag → a word
        // boundary. Otherwise VoiceOver's "s<break/>sierra" (letter + phonetic)
        // would merge into "ssierra". (eSpeak avoids this by parsing SSML itself.)
        var s = ssml.replacingOccurrences(of: "<break[^>]*>", with: "\n",
                                          options: [.regularExpression, .caseInsensitive])
        s = s.replacingOccurrences(of: "<[^>]+>", with: " ", options: .regularExpression)
        let entities = ["&amp;": "&", "&lt;": "<", "&gt;": ">",
                        "&quot;": "\"", "&apos;": "'", "&#39;": "'"]
        for (k, v) in entities { s = s.replacingOccurrences(of: k, with: v) }
        // Collapse runs of spaces/tabs but keep newlines (phrase boundaries).
        s = s.replacingOccurrences(of: "[ \\t]+", with: " ", options: .regularExpression)
        return s.trimmingCharacters(in: .whitespacesAndNewlines)
    }
}
