import SwiftUI
import AVFAudio
import LiepaCore

@main
struct LiepaApp: App {
    init() {
        // First launch: copy bundled voices/rules into the shared App Group so
        // both the app and the extension use one writable location.
        VoiceManager.installBundledVoicesIfNeeded()
        // Make the system (re)scan our provider voices.
        AVSpeechSynthesisProviderVoice.updateSpeechVoices()
    }
    var body: some Scene {
        WindowGroup {
            ContentView()
                .preferredColorScheme(.dark)   // LIEPA dark theme
                .tint(Color.liepaTeal)
        }
    }
}
