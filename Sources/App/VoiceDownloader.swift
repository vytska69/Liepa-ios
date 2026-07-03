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

/// Downloads voice bases (.rar) from the LIEPA server, extracts them with the
/// vendored unrar into the shared App Group, and manages installed qualities.
@MainActor
final class VoiceDownloader: NSObject, ObservableObject {
    enum State: Equatable {
        case idle
        case downloading(Double)
        case extracting
        case failed(String)
    }

    /// Voices+variants parsed from the server index.
    @Published var variants: [VoiceVariant] = []
    /// In-flight download/extract state, keyed by voice.
    @Published var states: [LiepaVoice: State] = [:]
    /// Bumped whenever installed state changes, to refresh views.
    @Published var revision = 0
    @Published var indexError: String?

    private let indexURL = "https://klevas.mif.vu.lt/~pijus/android/Garsu_bazes/"

    private var tasks: [LiepaVoice: URLSessionDownloadTask] = [:]
    private var observations: [LiepaVoice: NSKeyValueObservation] = [:]
    private var pendingQuality: [LiepaVoice: Int] = [:]
    private var lastAnnounced: [LiepaVoice: Int] = [:]
    private lazy var session = URLSession(configuration: .default,
                                          delegate: self, delegateQueue: nil)

    override init() {
        super.init()
        for v in LiepaVoice.allCases { states[v] = .idle }
    }

    /// Speak download progress through VoiceOver at 25% milestones.
    private func announceProgress(_ voice: LiepaVoice, _ fraction: Double) {
        guard UIAccessibility.isVoiceOverRunning else { return }
        let milestone = Int(fraction * 4) * 25          // 0,25,50,75,100
        guard milestone > 0, lastAnnounced[voice] != milestone else { return }
        lastAnnounced[voice] = milestone
        UIAccessibility.post(notification: .announcement,
                             argument: "\(voice.displayName): atsisiųsta \(milestone) procentų")
    }

    // MARK: installed queries (pass-through to VoiceManager)

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

    // MARK: management

    func download(_ variant: VoiceVariant) {
        let voice = variant.voice
        guard let url = URL(string: indexURL + variant.filename) else { return }
        if case .downloading = states[voice] { return }   // one download per voice at a time
        pendingQuality[voice] = variant.quality
        lastAnnounced[voice] = 0
        states[voice] = .downloading(0)
        let task = session.downloadTask(with: url)
        task.taskDescription = "\(voice.folderName)|\(variant.quality)"
        tasks[voice] = task
        observations[voice] = task.progress.observe(\.fractionCompleted) { [weak self] p, _ in
            Task { @MainActor in
                self?.states[voice] = .downloading(p.fractionCompleted)
                self?.announceProgress(voice, p.fractionCompleted)
            }
        }
        task.resume()
    }

    func cancel(_ voice: LiepaVoice) {
        tasks[voice]?.cancel(); tasks[voice] = nil
        states[voice] = .idle
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
    }

    nonisolated private static func findFile(named name: String, under dir: URL, fm: FileManager) -> URL? {
        guard let en = fm.enumerator(at: dir, includingPropertiesForKeys: nil) else { return nil }
        for case let u as URL in en where u.lastPathComponent == name { return u }
        return nil
    }
}

extension VoiceDownloader: URLSessionDownloadDelegate {
    nonisolated func urlSession(_ session: URLSession, downloadTask: URLSessionDownloadTask,
                                didFinishDownloadingTo location: URL) {
        let parts = (downloadTask.taskDescription ?? "").split(separator: "|")
        guard parts.count == 2,
              let voice = LiepaVoice.allCases.first(where: { $0.folderName == parts[0] }),
              let quality = Int(parts[1]) else { return }
        let tmp = FileManager.default.temporaryDirectory.appendingPathComponent(UUID().uuidString + ".rar")
        try? FileManager.default.moveItem(at: location, to: tmp)
        Task { @MainActor in self.states[voice] = .extracting }
        do {
            try install(rarAt: tmp, voice: voice, quality: quality)
            try? FileManager.default.removeItem(at: tmp)
            Task { @MainActor in
                self.states[voice] = .idle
                VoiceManager.ensureDefault(voice)      // first quality becomes default
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
        guard let error, let voice = LiepaVoice.allCases.first(where: {
            (task.taskDescription ?? "").hasPrefix($0.folderName)
        }) else { return }
        Task { @MainActor in
            if case .extracting = self.states[voice] { return }
            self.states[voice] = .failed(error.localizedDescription)
        }
    }
}
