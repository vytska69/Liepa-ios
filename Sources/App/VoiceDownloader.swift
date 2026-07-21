import Foundation
import AVFAudio
import UIKit
import LiepaCore
// liepa_unrar_extract is exposed via the app's bridging header.

/// One downloadable voice base from the LIEPA server, e.g. Regina @ quality 50.
struct VoiceVariant: Identifiable, Hashable {
    let voice: LiepaVoice
    let quality: Int          // 15 / 20 / 50 / 100
    let size: Int64           // bytes (0 if unknown)
    var id: String { "\(voice.folderName)\(quality)" }
    var filename: String { "\(voice.folderName)\(quality).rar" }
    var sizeText: String {
        size > 0 ? ByteCountFormatter.string(fromByteCount: size, countStyle: .file) : ""
    }
}

/// Downloads voice bases (.rar) from the LIEPA server via a **background**
/// URLSession (downloads continue when the app is suspended/closed), extracts
/// them with the vendored unrar into the shared App Group, and manages
/// installed qualities.
@MainActor
final class VoiceDownloader: NSObject, ObservableObject {
    /// Shared instance — a background session must live for the whole app so it
    /// can receive completion events after a relaunch.
    static let shared = VoiceDownloader()

    enum State: Equatable {
        case idle
        case downloading(Double)
        case paused(Double)
        case extracting
        case failed(String)
    }

    @Published var variants: [VoiceVariant] = []
    @Published var states: [LiepaVoice: State] = [:]
    @Published var revision = 0
    @Published var indexError: String?

    /// Completion handler handed to us by the system when the app is relaunched
    /// to finish background transfers.
    var backgroundCompletion: (() -> Void)?

    private let indexURL = "https://klevas.mif.vu.lt/~pijus/android/Garsu_bazes/"
    private static let sessionID = "lt.liepa.tts.voicedownload"

    private var session: URLSession!

    /// Resume data + task description ("<Name>|<quality>") kept while a download
    /// is paused, so it can be resumed where it left off.
    private var resumeInfo: [LiepaVoice: (data: Data, desc: String)] = [:]

    private override init() {
        super.init()
        let cfg = URLSessionConfiguration.background(withIdentifier: Self.sessionID)
        cfg.sessionSendsLaunchEvents = true    // wake the app when done
        cfg.isDiscretionary = false            // start promptly
        cfg.allowsCellularAccess = true
        session = URLSession(configuration: cfg, delegate: self, delegateQueue: nil)
        for v in LiepaVoice.allCases { states[v] = .idle }
        // Re-attach state for any transfers still running from a previous launch.
        session.getAllTasks { tasks in
            Task { @MainActor in
                for t in tasks {
                    if let v = Self.voice(fromTaskDescription: t.taskDescription),
                       t.state == .running {
                        self.states[v] = .downloading(0)
                    }
                }
            }
        }
    }

    // MARK: installed queries (pass-through)

    func installedQualities(_ v: LiepaVoice) -> [Int] { VoiceManager.installedQualities(v) }
    func defaultQuality(_ v: LiepaVoice) -> Int? { VoiceManager.defaultQuality(v) }
    var installedVoices: [LiepaVoice] { VoiceManager.installedVoices() }

    // MARK: index

    func loadIndex() async {
        guard let url = URL(string: indexURL) else { return }
        do {
            let (data, _) = try await URLSession.shared.data(from: url)
            let html = String(decoding: data, as: UTF8.self)
            variants = Self.parseIndex(html)
            indexError = variants.isEmpty ? "Indekse balsų nerasta" : nil
        } catch {
            indexError = error.localizedDescription
        }
    }

    nonisolated static func parseIndex(_ html: String) -> [VoiceVariant] {
        let names = LiepaVoice.allCases.map { $0.folderName }.joined(separator: "|")
        let pattern = "href=\"(\(names))(15|20|50|100)\\.rar\""
        guard let re = try? NSRegularExpression(pattern: pattern) else { return [] }
        let ns = html as NSString
        var seen = Set<String>()
        var out: [VoiceVariant] = []
        for m in re.matches(in: html, range: NSRange(location: 0, length: ns.length)) {
            let name = ns.substring(with: m.range(at: 1))
            let q = Int(ns.substring(with: m.range(at: 2))) ?? 0
            guard let voice = LiepaVoice.allCases.first(where: { $0.folderName == name }) else { continue }
            if seen.insert("\(name)\(q)").inserted {
                out.append(VoiceVariant(voice: voice, quality: q,
                                        size: sizeAfter(filename: "\(name)\(q).rar", in: html)))
            }
        }
        return out.sorted { ($0.voice.displayName, $0.quality) < ($1.voice.displayName, $1.quality) }
    }

    nonisolated private static func sizeAfter(filename: String, in html: String) -> Int64 {
        guard let r = html.range(of: filename) else { return 0 }
        let tail = html[r.upperBound...].prefix(160)
        guard let m = tail.range(of: "([0-9]+(?:\\.[0-9]+)?)\\s*([KMG])", options: .regularExpression)
        else { return 0 }
        let s = tail[m]
        let num = Double(s.prefix(while: { $0.isNumber || $0 == "." })) ?? 0
        let mult: Double = s.contains("G") ? 1_073_741_824 : s.contains("M") ? 1_048_576 : 1_024
        return Int64(num * mult)
    }

    // MARK: task description helpers ("<Name>|<quality>")

    nonisolated static func voice(fromTaskDescription d: String?) -> LiepaVoice? {
        guard let name = d?.split(separator: "|").first else { return nil }
        return LiepaVoice.allCases.first { $0.folderName == name }
    }
    nonisolated static func quality(fromTaskDescription d: String?) -> Int? {
        guard let parts = d?.split(separator: "|"), parts.count == 2 else { return nil }
        return Int(parts[1])
    }

    // MARK: management

    func download(_ variant: VoiceVariant) {
        let voice = variant.voice
        guard let url = URL(string: indexURL + variant.filename) else { return }
        if case .downloading = states[voice] { return }
        states[voice] = .downloading(0)
        let task = session.downloadTask(with: url)
        task.taskDescription = "\(voice.folderName)|\(variant.quality)"
        task.resume()
    }

    func cancel(_ voice: LiepaVoice) {
        session.getAllTasks { tasks in
            for t in tasks where Self.voice(fromTaskDescription: t.taskDescription) == voice { t.cancel() }
        }
        resumeInfo[voice] = nil
        states[voice] = .idle
    }

    /// Pause an in-flight download, keeping resume data so it can continue later.
    func pause(_ voice: LiepaVoice) {
        let progress: Double = { if case .downloading(let p) = states[voice] { return p } else { return 0 } }()
        session.getAllTasks { tasks in
            guard let task = tasks.first(where: {
                Self.voice(fromTaskDescription: $0.taskDescription) == voice
            }) as? URLSessionDownloadTask else {
                Task { @MainActor in self.states[voice] = .paused(progress) }
                return
            }
            let desc = task.taskDescription ?? "\(voice.folderName)|"
            task.cancel(byProducingResumeData: { data in
                Task { @MainActor in
                    if let data { self.resumeInfo[voice] = (data, desc) }
                    self.states[voice] = .paused(progress)
                }
            })
        }
    }

    /// Resume a paused download from where it stopped (or restart if the server
    /// couldn't produce resume data).
    func resume(_ voice: LiepaVoice) {
        let progress: Double = { if case .paused(let p) = states[voice] { return p } else { return 0 } }()
        guard let info = resumeInfo[voice] else { return }
        resumeInfo[voice] = nil
        let task = session.downloadTask(withResumeData: info.data)
        task.taskDescription = info.desc
        states[voice] = .downloading(progress)
        task.resume()
    }

    func setDefault(_ voice: LiepaVoice, quality: Int) {
        VoiceManager.setDefault(voice, quality: quality)
        revision += 1
        AVSpeechSynthesisProviderVoice.updateSpeechVoices()
    }

    func delete(_ voice: LiepaVoice, quality: Int) {
        VoiceManager.delete(voice, quality: quality)
        revision += 1
        AVSpeechSynthesisProviderVoice.updateSpeechVoices()
    }

    func deleteAll(_ voice: LiepaVoice) {
        VoiceManager.deleteAll(voice)
        revision += 1
        AVSpeechSynthesisProviderVoice.updateSpeechVoices()
    }

    // MARK: extraction (off main)

    nonisolated private func install(rarAt rarURL: URL, voice: LiepaVoice, quality: Int) throws {
        let fm = FileManager.default
        let temp = fm.temporaryDirectory.appendingPathComponent(UUID().uuidString)
        try fm.createDirectory(at: temp, withIntermediateDirectories: true)
        defer { try? fm.removeItem(at: temp) }
        let rc = liepa_unrar_extract(rarURL.path, temp.path)
        guard rc == 0 else {
            throw NSError(domain: "Liepa", code: Int(rc),
                          userInfo: [NSLocalizedDescriptionKey: "Nepavyko išskleisti archyvo (rc=\(rc))"])
        }
        guard let dbRaw = Self.findFile(named: "db.raw", under: temp, fm: fm) else {
            throw NSError(domain: "Liepa", code: 2,
                          userInfo: [NSLocalizedDescriptionKey: "db.raw nerasta archyve"])
        }
        let srcDir = dbRaw.deletingLastPathComponent()
        guard let dest = VoiceManager.installDir(voice, quality: quality) else {
            throw NSError(domain: "Liepa", code: 3)
        }
        try? fm.removeItem(at: dest)
        try fm.createDirectory(at: dest.deletingLastPathComponent(), withIntermediateDirectories: true)
        try fm.moveItem(at: srcDir, to: dest)
        // Make the new voice readable before first unlock (lock screen after a
        // reboot), matching how the app group data is otherwise protected.
        VoiceManager.applyDataProtectionNone()
    }

    nonisolated private static func findFile(named name: String, under dir: URL, fm: FileManager) -> URL? {
        guard let en = fm.enumerator(at: dir, includingPropertiesForKeys: nil) else { return nil }
        for case let u as URL in en where u.lastPathComponent == name { return u }
        return nil
    }
}

extension VoiceDownloader: URLSessionDownloadDelegate {
    // progress
    nonisolated func urlSession(_ session: URLSession, downloadTask: URLSessionDownloadTask,
                                didWriteData bytesWritten: Int64, totalBytesWritten: Int64,
                                totalBytesExpectedToWrite: Int64) {
        guard totalBytesExpectedToWrite > 0,
              let voice = Self.voice(fromTaskDescription: downloadTask.taskDescription) else { return }
        let p = Double(totalBytesWritten) / Double(totalBytesExpectedToWrite)
        Task { @MainActor in self.states[voice] = .downloading(p) }
    }

    // download finished → extract + install (runs even when relaunched in background)
    nonisolated func urlSession(_ session: URLSession, downloadTask: URLSessionDownloadTask,
                                didFinishDownloadingTo location: URL) {
        guard let voice = Self.voice(fromTaskDescription: downloadTask.taskDescription),
              let quality = Self.quality(fromTaskDescription: downloadTask.taskDescription) else { return }
        // The temp file is deleted when this returns — move it out first.
        let tmp = FileManager.default.temporaryDirectory.appendingPathComponent(UUID().uuidString + ".rar")
        try? FileManager.default.moveItem(at: location, to: tmp)
        Task { @MainActor in self.states[voice] = .extracting }
        do {
            try install(rarAt: tmp, voice: voice, quality: quality)
            try? FileManager.default.removeItem(at: tmp)
            Task { @MainActor in
                self.states[voice] = .idle
                VoiceManager.ensureDefault(voice)
                self.revision += 1
                AVSpeechSynthesisProviderVoice.updateSpeechVoices()
            }
        } catch {
            try? FileManager.default.removeItem(at: tmp)
            Task { @MainActor in self.states[voice] = .failed(error.localizedDescription) }
        }
    }

    nonisolated func urlSession(_ session: URLSession, task: URLSessionTask,
                                didCompleteWithError error: Error?) {
        guard let error, let voice = Self.voice(fromTaskDescription: task.taskDescription) else { return }
        // .cancelled is user-initiated; ignore.
        if (error as NSError).code == NSURLErrorCancelled { return }
        Task { @MainActor in
            if case .extracting = self.states[voice] { return }
            self.states[voice] = .failed(error.localizedDescription)
        }
    }

    // all background events delivered → let the system suspend us again
    nonisolated func urlSessionDidFinishEvents(forBackgroundURLSession session: URLSession) {
        Task { @MainActor in
            self.backgroundCompletion?()
            self.backgroundCompletion = nil
        }
    }
}
