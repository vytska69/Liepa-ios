import SwiftUI
import LiepaCore

/// The app's text-normalisation settings, mirroring the Android app's
/// `general_settings.xml` (minus voice & pitch, which VoiceOver controls).
///
/// Stored in the shared App Group so the Speech-provider extension reads the
/// same values. Defaults match the Android app:
///   skaičiai = Įprastai(4), skyryba = Išjungta(1), santrumpos = on, emoji = off.
final class SynthSettings: ObservableObject {
    static let appGroup = "group.lt.liepa.tts"
    static var store: UserDefaults { UserDefaults(suiteName: appGroup) ?? .standard }

    @AppStorage("lith_tts_santrumpos", store: SynthSettings.store)
    var expandAbbreviations: Bool = true        // Santrumpų išskleidimas (on/off)
    @AppStorage("lith_tts_skaiciai", store: SynthSettings.store)
    var numbersLevel: Int = 4                    // Skaičių įgarsinimas (1–4)
    @AppStorage("lith_tts_skyryba", store: SynthSettings.store)
    var punctuationLevel: Int = 1                // Skyryba (1–4)
    @AppStorage("lith_tts_emoji", store: SynthSettings.store)
    var readEmoji: Bool = false                  // Emodži skaitymas (on/off)

    var modes: LiepaModes {
        LiepaModes(abbreviations: expandAbbreviations,
                   numbers: LiepaNumbers(rawValue: numbersLevel) ?? .normal,
                   punctuation: LiepaPunctuation(rawValue: punctuationLevel) ?? .off,
                   emoji: readEmoji)
    }
}
