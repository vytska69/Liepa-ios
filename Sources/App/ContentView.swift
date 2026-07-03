import SwiftUI
import LiepaCore

struct ContentView: View {
    @StateObject private var settings = SynthSettings()

    private let numberOptions: [(Int, String)] =
        [(1, "Po vieną"), (2, "Po du"), (3, "Po tris"), (4, "Įprastai")]
    private let punctuationOptions: [(Int, String)] =
        [(1, "Išjungta"), (2, "Kai kurie"), (3, "Dauguma"), (4, "Visi")]

    var body: some View {
        NavigationStack {
            Form {
                Section("Teksto apdorojimas") {
                    Picker("Skaičių įgarsinimas", selection: $settings.numbersLevel) {
                        ForEach(numberOptions, id: \.0) { Text($0.1).tag($0.0) }
                    }
                    Picker("Skyryba", selection: $settings.punctuationLevel) {
                        ForEach(punctuationOptions, id: \.0) { Text($0.1).tag($0.0) }
                    }
                    Toggle("Santrumpų išskleidimas", isOn: $settings.expandAbbreviations)
                    Toggle("Emodži skaitymas", isOn: $settings.readEmoji)
                }

                Section("Balsai") {
                    NavigationLink {
                        VoicesView()
                    } label: {
                        Label("Tvarkyti balsus", systemImage: "person.wave.2.fill")
                    }
                }
            }
            .scrollContentBackground(.hidden)
            .background(Color.black.ignoresSafeArea())
            .navigationTitle("Liepa")
        }
    }
}

#Preview {
    ContentView()
}
