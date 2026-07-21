import Foundation

/// Manages voice bases in the shared App Group `liepa-data/`.
///
/// Multiple quality bases of one voice may be installed at once, stored as
/// `liepa-data/<Name><quality>/` (e.g. `Regina50`, `Regina100`). The engine
/// always loads `liepa-data/<Name>/`, which is a **symlink** to the chosen
/// default-quality base. Switching the default just repoints the symlink.
public enum VoiceManager {
    public static let appGroup = "group.lt.liepa.tts"
    public static let qualities = [15, 20, 50, 100]

    private static var fm: FileManager { .default }

    public static var containerURL: URL? {
        fm.containerURL(forSecurityApplicationGroupIdentifier: appGroup)
    }
    public static var sharedDataDir: URL? {
        containerURL?.appendingPathComponent("liepa-data", isDirectory: true)
    }
    public static var bundleDataDir: URL? {
        Bundle.main.resourceURL?.appendingPathComponent("liepa-data", isDirectory: true)
    }

    /// Directory that *contains* `liepa-data` for the engine. App Group first,
    /// then bundle fallback.
    public static func dataParentPath() -> String? {
        if let shared = sharedDataDir, fm.fileExists(atPath: shared.path) {
            return containerURL?.path
        }
        if let res = Bundle.main.resourceURL,
           fm.fileExists(atPath: res.appendingPathComponent("liepa-data").path) {
            return res.path
        }
        if let plugins = Bundle.main.builtInPlugInsURL,
           let entries = try? fm.contentsOfDirectory(at: plugins, includingPropertiesForKeys: nil) {
            for appex in entries where appex.pathExtension == "appex" {
                if let r = Bundle(url: appex)?.resourceURL,
                   fm.fileExists(atPath: r.appendingPathComponent("liepa-data").path) {
                    return r.path
                }
            }
        }
        return nil
    }

    /// `liepa-data` directory (read location).
    private static func dataDir() -> URL? {
        dataParentPath().map { URL(fileURLWithPath: $0).appendingPathComponent("liepa-data") }
    }

    static func baseDir(_ data: URL, _ v: LiepaVoice, _ q: Int) -> URL {
        data.appendingPathComponent("\(v.folderName)\(q)", isDirectory: true)
    }
    static func voiceLink(_ data: URL, _ v: LiepaVoice) -> URL {
        data.appendingPathComponent(v.folderName, isDirectory: true)
    }

    // MARK: queries

    /// Quality bases installed for a voice (each has a db.raw).
    public static func installedQualities(_ v: LiepaVoice) -> [Int] {
        guard let d = dataDir() else { return [] }
        return qualities.filter {
            fm.fileExists(atPath: baseDir(d, v, $0).appendingPathComponent("db.raw").path)
        }
    }

    /// The quality the engine currently uses (the symlink target).
    public static func defaultQuality(_ v: LiepaVoice) -> Int? {
        guard let d = dataDir(),
              let dest = try? fm.destinationOfSymbolicLink(atPath: voiceLink(d, v).path)
        else { return nil }
        let name = (dest as NSString).lastPathComponent
        return qualities.first { name == "\(v.folderName)\($0)" }
    }

    /// Voices with a usable default (the engine link resolves to a db.raw).
    public static func installedVoices() -> [LiepaVoice] {
        guard let d = dataDir() else { return [] }
        return LiepaVoice.allCases.filter {
            fm.fileExists(atPath: voiceLink(d, $0).appendingPathComponent("db.raw").path)
        }
    }
    public static func isInstalled(_ v: LiepaVoice) -> Bool { installedVoices().contains(v) }

    // MARK: mutations

    public static func installDir(_ v: LiepaVoice, quality q: Int) -> URL? {
        sharedDataDir?.appendingPathComponent("\(v.folderName)\(q)", isDirectory: true)
    }

    /// Point the engine link at a specific installed quality.
    @discardableResult
    public static func setDefault(_ v: LiepaVoice, quality q: Int) -> Bool {
        guard let d = sharedDataDir else { return false }
        let link = voiceLink(d, v)
        // Only ever remove a symlink here (never a real data dir).
        if (try? fm.destinationOfSymbolicLink(atPath: link.path)) != nil {
            try? fm.removeItem(at: link)
        } else if !fm.fileExists(atPath: link.path) {
            // nothing to remove
        } else {
            // A real dir occupies the link slot (legacy) — migrate it away first.
            migrateLegacy(v)
            try? fm.removeItem(at: link)
        }
        return (try? fm.createSymbolicLink(atPath: link.path,
                                           withDestinationPath: "\(v.folderName)\(q)")) != nil
    }

    /// Ensure a voice has a default symlink (pick the highest installed quality).
    public static func ensureDefault(_ v: LiepaVoice) {
        guard let d = dataDir() else { return }
        if fm.fileExists(atPath: voiceLink(d, v).appendingPathComponent("db.raw").path) { return }
        if let best = installedQualities(v).max() { setDefault(v, quality: best) }
    }

    /// Delete one quality base. Repoints/removes the default link as needed.
    public static func delete(_ v: LiepaVoice, quality q: Int) {
        guard let d = sharedDataDir else { return }
        let wasDefault = defaultQuality(v) == q
        try? fm.removeItem(at: baseDir(d, v, q))
        if wasDefault || defaultQuality(v) == nil {
            try? fm.removeItem(at: voiceLink(d, v))   // safe: only a symlink
            if let best = installedQualities(v).max() { setDefault(v, quality: best) }
        }
    }

    /// Delete every quality of a voice.
    public static func deleteAll(_ v: LiepaVoice) {
        guard let d = sharedDataDir else { return }
        for q in installedQualities(v) { try? fm.removeItem(at: baseDir(d, v, q)) }
        try? fm.removeItem(at: voiceLink(d, v))
    }

    // MARK: setup / migration

    /// Copy the bundled shared rules into the App Group on first launch.
    @discardableResult
    public static func installBundledVoicesIfNeeded() -> Bool {
        guard let shared = sharedDataDir, let bundle = bundleDataDir,
              fm.fileExists(atPath: bundle.path) else { return false }
        try? fm.createDirectory(at: shared, withIntermediateDirectories: true)
        guard let items = try? fm.contentsOfDirectory(at: bundle, includingPropertiesForKeys: nil)
        else { return false }
        for src in items {
            let dst = shared.appendingPathComponent(src.lastPathComponent)
            // Shared front-end files (rules/abb/skaitm/inicialai/matvnt …) ship with
            // the app: always refresh them so engine updates take effect. Voice
            // folders live only in the App Group and are never in the bundle.
            let isDir = (try? src.resourceValues(forKeys: [.isDirectoryKey]))?.isDirectory ?? false
            if isDir {
                if !fm.fileExists(atPath: dst.path) { try? fm.copyItem(at: src, to: dst) }
            } else {
                try? fm.removeItem(at: dst)
                try? fm.copyItem(at: src, to: dst)
            }
        }
        for v in LiepaVoice.allCases { migrateLegacy(v) }
        // Voice data must be readable at the lock screen *before the first
        // unlock* (e.g. VoiceOver right after a reboot). iOS's default file
        // protection hides files until first unlock, so mark all voice data as
        // unprotected. Runs on every launch, so it also migrates voices already
        // installed under 1.0.
        applyDataProtectionNone()
        return true
    }

    /// Recursively set `FileProtectionType.none` on everything under
    /// `liepa-data`, so the Speech extension can read the voice bases before the
    /// device's first unlock after a reboot (Before First Unlock state).
    public static func applyDataProtectionNone() {
        guard let root = sharedDataDir, fm.fileExists(atPath: root.path) else { return }
        setProtectionNone(at: root)
        guard let en = fm.enumerator(at: root, includingPropertiesForKeys: nil) else { return }
        for case let url as URL in en { setProtectionNone(at: url) }
    }

    private static func setProtectionNone(at url: URL) {
        // Skip symlinks (the voice link) — the real target is handled separately.
        if (try? fm.destinationOfSymbolicLink(atPath: url.path)) != nil { return }
        try? fm.setAttributes([.protectionKey: FileProtectionType.none],
                              ofItemAtPath: url.path)
    }

    /// Convert a legacy real-dir `<Name>/` install into `<Name><q>/` + symlink.
    private static func migrateLegacy(_ v: LiepaVoice) {
        guard let d = sharedDataDir else { return }
        let link = voiceLink(d, v)
        // Skip if it's already a symlink or doesn't exist.
        if (try? fm.destinationOfSymbolicLink(atPath: link.path)) != nil { return }
        guard fm.fileExists(atPath: link.appendingPathComponent("db.raw").path) else { return }
        let store = UserDefaults(suiteName: appGroup)
        let q = store?.integer(forKey: "lith_voice_quality_\(v.folderName)") ?? 0
        let quality = qualities.contains(q) ? q : 50
        let dest = baseDir(d, v, quality)
        try? fm.removeItem(at: dest)
        do {
            try fm.moveItem(at: link, to: dest)
            try fm.createSymbolicLink(atPath: link.path,
                                      withDestinationPath: "\(v.folderName)\(quality)")
        } catch { /* leave as-is on failure */ }
    }
}
