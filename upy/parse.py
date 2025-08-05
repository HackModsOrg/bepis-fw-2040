import sys
import pretty_midi

midi_data = pretty_midi.PrettyMIDI('smasnug.mid')
midi_data = pretty_midi.PrettyMIDI('IevanPolka.mid')
midi_data = pretty_midi.PrettyMIDI('among us.mid')
midi_data = pretty_midi.PrettyMIDI('builttoscale.mid')
midi_data = pretty_midi.PrettyMIDI(sys.argv[1])

freqs = []

print(midi_data.instruments)

prev_end = 0
for note in midi_data.instruments[0].notes:
    delay = note.start - prev_end
    if delay != 0:
        freqs.append((0, round(delay, 2)),)
    #print(note, pretty_midi.note_number_to_hz(note.pitch))
    freq = pretty_midi.note_number_to_hz(note.pitch)
    duration = note.end-note.start
    freqs.append((round(freq, 2), round(duration, 2)),)
    prev_end = note.end

print(freqs)
