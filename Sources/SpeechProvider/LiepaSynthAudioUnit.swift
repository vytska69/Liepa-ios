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
        let (greitis, tonas) = Self.prosody(fromSSML: ssml)

        do {
            try ensureEngine()
            let pcm = try engine!.synthesize(text, voice: voice, greitis: greitis, tonas: tonas, modes: modes)
            let floats = pcm.samples.map { Float32($0) / 32767.0 }
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

    private func ensureEngine() throws {
        guard engine == nil else { return }
        guard let path = VoiceManager.dataParentPath() else {
            throw NSError(domain: "Liepa", code: 1,
                          userInfo: [NSLocalizedDescriptionKey: "liepa-data not found"])
        }
        engine = try LiepaSynth(dataParentPath: path)
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
    /// engine's `greitis` (30…300, 100 = normal, higher = slower) and `tonas`
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
        // the system's prosody rate is the opposite, so map inversely: greitis = 10000/rate%.
        let pr = max(neutral100("rate") ?? 100, 1)
        let greitis = Int32(min(max(10000.0 / pr, 30), 300))   // 100→100, 200→50(faster), 50→200(slower)
        // `tonas` maps directly from pitch% (higher = higher pitch).
        let tonas = Int32(min(max(neutral100("pitch") ?? 100, 50), 300))
        return (greitis, tonas)
    }

    /// Minimal SSML → plain text: drop tags, decode the common entities.
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
        var s = ssml.replacingOccurrences(of: "<[^>]+>", with: "",
                                          options: .regularExpression)
        let entities = ["&amp;": "&", "&lt;": "<", "&gt;": ">",
                        "&quot;": "\"", "&apos;": "'", "&#39;": "'"]
        for (k, v) in entities { s = s.replacingOccurrences(of: k, with: v) }
        return s.trimmingCharacters(in: .whitespacesAndNewlines)
    }
}
