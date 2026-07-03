//
//  LiepaSynth.swift
//  Thin Swift wrapper around the LIEPA LithUSS unit-selection engine.
//
//  The underlying C engine keeps global state and is NOT reentrant, so all
//  access is serialised through one actor-like serial queue and a single
//  shared instance per process.
//

import Foundation

/// One of the bundled LIEPA Lithuanian voices.
public enum LiepaVoice: String, CaseIterable, Sendable {
    case regina   = "en-AU"
    case edvardas = "en-ZA"
    case aiste    = "en-US"
    case vladas   = "en-GB"

    /// Voice directory name under `liepa-data/`.
    public var folderName: String {
        switch self {
        case .regina:   return "Regina"
        case .edvardas: return "Edvardas"
        case .aiste:    return "Aiste"
        case .vladas:   return "Vladas"
        }
    }

    public var displayName: String {
        switch self {
        case .regina:   return "Regina"
        case .edvardas: return "Edvardas"
        case .aiste:    return "Aistė"
        case .vladas:   return "Vladas"
        }
    }
}

/// Number-reading mode (mirrors the Android "Skaičių įgarsinimas" list).
public enum LiepaNumbers: Int, CaseIterable, Sendable {
    case oneByOne = 1   // Po vieną
    case byTwos   = 2   // Po du
    case byThrees = 3   // Po tris
    case normal   = 4   // Įprastai
}

/// Punctuation-reading level (mirrors the Android "Skyryba" list).
public enum LiepaPunctuation: Int, CaseIterable, Sendable {
    case off    = 1     // Išjungta
    case some   = 2     // Kai kurie
    case most   = 3     // Dauguma
    case all    = 4     // Visi
}

/// Text-normalisation modes, mirroring the Android app's settings + the engine's
/// `*_rezimas` parameters to synthesizeWholeText.
public struct LiepaModes: Sendable {
    public var abbreviations: Bool        // Santrumpų išskleidimas (on/off)
    public var numbers: LiepaNumbers      // Skaičių įgarsinimas (1–4)
    public var punctuation: LiepaPunctuation // Skyryba (1–4)
    public var emoji: Bool                // Emodži skaitymas (on/off)

    public init(abbreviations: Bool = true,
                numbers: LiepaNumbers = .normal,
                punctuation: LiepaPunctuation = .off,
                emoji: Bool = false) {
        self.abbreviations = abbreviations
        self.numbers = numbers
        self.punctuation = punctuation
        self.emoji = emoji
    }
    public static let `default` = LiepaModes()
}

public struct LiepaPCM: Sendable {
    public let samples: [Int16]
    public let sampleRate: Double
}

public enum LiepaError: Error { case initFailed, notInitialized, synthFailed }

public final class LiepaSynth: @unchecked Sendable {

    public static let sampleRate: Double = 22050

    private let queue = DispatchQueue(label: "lt.liepa.engine")
    private let bufferMs: Int32
    private var initialized = false

    public init(dataParentPath: String, bufferMs: Int32 = 60_000) throws {
        self.bufferMs = bufferMs
        var rcOut: Liepa_ERROR = EE_INTERNAL_ERROR
        queue.sync {
            // Preload an INSTALLED voice at init (the engine's built-in default is
            // "Regina/", which may not be installed → would crash in initLUSS).
            if let first = VoiceManager.installedVoices().first {
                (first.folderName + "/").withCString { Liepa_SetVoiceFolder($0) }
            }
            rcOut = dataParentPath.withCString { cpath in
                Liepa_Initialize(bufferMs, cpath, 0)
            }
        }
        guard rcOut == EE_OK else { throw LiepaError.initFailed }
        initialized = true
    }

    deinit { queue.sync { _ = Liepa_Terminate() } }

    /// - greitis: engine rate, 30…300, 100 = normal (higher = slower).
    /// - tonas:   engine pitch, 100 = normal (higher = higher).
    public func synthesize(_ text: String,
                           voice: LiepaVoice,
                           greitis: Int32 = 100,
                           tonas: Int32 = 100,
                           modes: LiepaModes = .default) throws -> LiepaPCM {
        guard initialized else { throw LiepaError.notInitialized }

        // The engine takes UTF-16 text + text-normalisation modes as parameters
        // (including emoji reading — no Swift-side emoji handling needed).
        let utf16 = Array(text.utf16)

        var result: [Int16]? = nil
        queue.sync {
            utf16.withUnsafeBufferPointer { textPtr in
                voice.rawValue.withCString { voicePtr in
                    var outbuf: UnsafeMutablePointer<Int16>? = nil
                    var numSamples: UInt32 = 0
                    let rc = Liepa_Synth(textPtr.baseAddress, utf16.count,
                                         greitis, tonas,
                                         Int32(modes.numbers.rawValue),
                                         Int32(modes.punctuation.rawValue),
                                         modes.abbreviations ? 1 : 0,
                                         modes.emoji ? 1 : 0,
                                         voicePtr, &outbuf, &numSamples)
                    if (rc == EE_OK || rc == EE_BUFFER_FULL),
                       let outbuf = outbuf, numSamples > 0 {
                        result = Array(UnsafeBufferPointer(start: outbuf, count: Int(numSamples)))
                    }
                }
            }
        }
        guard let samples = result else { throw LiepaError.synthFailed }
        return LiepaPCM(samples: samples, sampleRate: Self.sampleRate)
    }
}
