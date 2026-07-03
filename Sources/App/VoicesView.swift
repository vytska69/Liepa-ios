import SwiftUI
import LiepaCore

/// "Tvarkyti balsus" — manage installed voices and download new ones.
///
/// Designed VoiceOver-first: each voice is a single accessibility element whose
/// operations (set default quality, delete, download) live in the **Actions
/// rotor** (`accessibilityActions`). A visual menu mirrors them for sighted use.
struct VoicesView: View {
    @ObservedObject private var downloader = VoiceDownloader.shared

    var body: some View {
        List {
            installedSection
            serverSection
        }
        .navigationTitle("Tvarkyti balsus")
        .task { await downloader.loadIndex() }
    }

    // MARK: Installed

    private var installedSection: some View {
        Section {
            let installed = downloader.installedVoices
            if installed.isEmpty {
                Text("Nėra įdiegtų balsų. Atsisiųskite žemiau, skiltyje Visi balsai.")
                    .font(.footnote).foregroundStyle(.secondary)
            }
            ForEach(installed, id: \.self) { installedRow($0) }
        } header: {
            Text("Įdiegti balsai")
        }
    }

    @ViewBuilder
    private func installedRow(_ voice: LiepaVoice) -> some View {
        let qs = downloader.installedQualities(voice)
        let def = downloader.defaultQuality(voice)
        let state = downloader.states[voice] ?? .idle

        VStack(alignment: .leading, spacing: 4) {
            HStack {
                Text(voice.displayName).font(.headline)
                Spacer()
                if qs.count > 1 || qs.first != def {
                    installedMenu(voice, qs, def).accessibilityHidden(true)
                }
            }
            Text(installedSummary(qs, def)).font(.footnote).foregroundStyle(.secondary)
            inlineProgress(state)
        }
        .accessibilityElement(children: .ignore)
        .accessibilityLabel("\(voice.displayName). \(installedSummary(qs, def))")
        .accessibilityValue(progressA11y(state))
        .accessibilityActions {
            ForEach(qs, id: \.self) { q in
                if q != def {
                    Button("Numatyta kokybė: \(qLabel(q))") { downloader.setDefault(voice, quality: q) }
                }
            }
            if qs.count == 1, let only = qs.first {
                Button("Ištrinti balsą") { downloader.delete(voice, quality: only) }
            } else {
                ForEach(qs, id: \.self) { q in
                    Button("Ištrinti: \(qLabel(q))") { downloader.delete(voice, quality: q) }
                }
            }
        }
    }

    private func installedMenu(_ voice: LiepaVoice, _ qs: [Int], _ def: Int?) -> some View {
        Menu {
            if qs.count > 1 {
                Section("Numatyta kokybė") {
                    ForEach(qs, id: \.self) { q in
                        Button { downloader.setDefault(voice, quality: q) } label: {
                            Label(qLabel(q), systemImage: q == def ? "checkmark" : "")
                        }
                    }
                }
            }
            Section("Ištrinti") {
                ForEach(qs, id: \.self) { q in
                    Button(role: .destructive) { downloader.delete(voice, quality: q) } label: {
                        Text(qs.count == 1 ? "Ištrinti balsą" : "Ištrinti: \(qLabel(q))")
                    }
                }
            }
        } label: {
            Image(systemName: "ellipsis.circle")
        }
    }

    // MARK: Server (all voices)

    private var serverSection: some View {
        Section {
            if downloader.variants.isEmpty {
                if let err = downloader.indexError {
                    Text("Nepavyko gauti sąrašo: \(err)").font(.footnote).foregroundStyle(.red)
                } else {
                    HStack { ProgressView(); Text("Kraunamas sąrašas…").foregroundStyle(.secondary) }
                }
            }
            ForEach(serverVoices, id: \.self) { serverRow($0) }
        } header: {
            Text("Visi balsai")
        }
    }

    private var serverVoices: [LiepaVoice] {
        LiepaVoice.allCases.filter { v in downloader.variants.contains { $0.voice == v } }
    }

    @ViewBuilder
    private func serverRow(_ voice: LiepaVoice) -> some View {
        let vars = downloader.variants.filter { $0.voice == voice }
        let installed = Set(downloader.installedQualities(voice))
        let state = downloader.states[voice] ?? .idle

        VStack(alignment: .leading, spacing: 4) {
            HStack {
                Text(voice.displayName).font(.headline)
                Spacer()
                serverMenu(voice, vars, installed).accessibilityHidden(true)
            }
            Text(serverSummary(vars, installed)).font(.footnote).foregroundStyle(.secondary)
            inlineProgress(state, cancellable: voice)
        }
        .accessibilityElement(children: .ignore)
        .accessibilityLabel("\(voice.displayName). \(serverSummary(vars, installed))")
        .accessibilityValue(progressA11y(state))
        .accessibilityActions {
            ForEach(vars) { v in
                if !installed.contains(v.quality) {
                    Button("Atsisiųsti: \(qLabel(v.quality))\(v.sizeText.isEmpty ? "" : ", \(v.sizeText)")") {
                        downloader.download(v)
                    }
                }
            }
        }
    }

    private func serverMenu(_ voice: LiepaVoice, _ vars: [VoiceVariant], _ installed: Set<Int>) -> some View {
        Menu {
            ForEach(vars) { v in
                Button { downloader.download(v) } label: {
                    Label(installed.contains(v.quality)
                          ? "\(qLabel(v.quality)) (įdiegta)"
                          : "Atsisiųsti: \(qLabel(v.quality))\(v.sizeText.isEmpty ? "" : " · \(v.sizeText)")",
                          systemImage: installed.contains(v.quality) ? "checkmark" : "arrow.down.circle")
                }
                .disabled(installed.contains(v.quality))
            }
        } label: {
            Image(systemName: "arrow.down.circle")
        }
    }

    // MARK: shared bits

    @ViewBuilder
    private func inlineProgress(_ state: VoiceDownloader.State, cancellable voice: LiepaVoice? = nil) -> some View {
        switch state {
        case .downloading(let p):
            VStack(alignment: .leading, spacing: 4) {
                ProgressView(value: p) { Text("Atsisiunčiama… \(Int(p * 100))%").font(.footnote) }
                if let voice { Button("Atšaukti") { downloader.cancel(voice) }.font(.footnote) }
            }
        case .extracting:
            HStack { ProgressView(); Text("Skleidžiama…").font(.footnote).foregroundStyle(.secondary) }
        case .failed(let msg):
            Text("Klaida: \(msg)").font(.footnote).foregroundStyle(.red)
        case .idle:
            EmptyView()
        }
    }

    private func installedSummary(_ qs: [Int], _ def: Int?) -> String {
        guard !qs.isEmpty else { return "neįdiegta" }
        let parts = qs.map { q in q == def ? "\(qLabel(q)) (numatyta)" : qLabel(q) }
        return "Įdiegta: " + parts.joined(separator: ", ")
    }

    private func serverSummary(_ vars: [VoiceVariant], _ installed: Set<Int>) -> String {
        let available = vars.map { $0.quality }.filter { !installed.contains($0) }
        if available.isEmpty { return "visos kokybės įdiegtos" }
        return "Galima atsisiųsti: " + available.map { qLabel($0) }.joined(separator: ", ")
    }

    private func progressA11y(_ state: VoiceDownloader.State) -> String {
        switch state {
        case .downloading(let p): return "atsisiunčiama, \(Int(p * 100)) procentų"
        case .extracting:         return "skleidžiama"
        case .failed(let m):      return "klaida: \(m)"
        case .idle:               return ""
        }
    }

    private func qLabel(_ q: Int) -> String {
        switch q {
        case 15:  return "Pagrindinė"
        case 20:  return "Gera"
        case 50:  return "Aukšta"
        case 100: return "Aukščiausia"
        default:  return "Kokybė \(q)"
        }
    }
}
