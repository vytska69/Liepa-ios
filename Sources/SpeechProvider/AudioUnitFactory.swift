import CoreAudioKit

/// Principal class of the Speech-synthesis-provider extension. The system
/// instantiates this and asks it for the audio unit that produces speech.
public class AudioUnitFactory: NSObject, AUAudioUnitFactory {
    public func beginRequest(with context: NSExtensionContext) {}

    @objc public func createAudioUnit(
        with componentDescription: AudioComponentDescription
    ) throws -> AUAudioUnit {
        try LiepaSynthAudioUnit(componentDescription: componentDescription, options: [])
    }
}
