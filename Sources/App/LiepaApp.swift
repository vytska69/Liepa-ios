import SwiftUI
import UIKit
import AVFAudio
import LiepaCore

/// Receives background-URLSession completion events so voice downloads can
/// finish while the app is suspended.
final class AppDelegate: NSObject, UIApplicationDelegate {
    func application(_ application: UIApplication,
                     handleEventsForBackgroundURLSession identifier: String,
                     completionHandler: @escaping () -> Void) {
        VoiceDownloader.shared.backgroundCompletion = completionHandler
    }
}

@main
struct LiepaApp: App {
    @UIApplicationDelegateAdaptor(AppDelegate.self) private var appDelegate

    init() {
        // First launch: copy bundled rules into the shared App Group.
        VoiceManager.installBundledVoicesIfNeeded()
        // Create the background download session early so it can receive events.
        _ = VoiceDownloader.shared
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
