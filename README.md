# Test

```bash
sudo modprobe snd_seq_midi
fluidsynth --server --audio-driver=pulseaudio /usr/share/soundfonts/freepats-general-midi.sf2
aconnect 20 128
```

