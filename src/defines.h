/* MIDI CC# */
#define CC_OSC1_VOLUME 11
#define CC_OSC2_VOLUME 12
#define CC_OSC3_VOLUME 13
#define CC_NOISE_VOLUME 14

#define CC_OSC1_SHAPE 15
#define CC_OSC2_SHAPE 16
#define CC_OSC3_SHAPE 17
#define CC_DETUNE 18

#define CC_OSC1_OCTAVE 19
#define CC_OSC2_OCTAVE 20
#define CC_OSC3_OCTAVE 21
#define CC_LFO1_PITCH_DEPTH 22

#define CC_LFO1_SHAPE 23
#define CC_LFO1_FREQ 24
#define CC_LFO1_ 25
#define CC_LFO1__ 26

#define CC_LFO2_SHAPE 27
#define CC_LFO2_FREQ 28
#define CC_LFO2_ 29
#define CC_LFO2__ 30

#define CC_FILTER_FREQ 31
#define CC_FILTER_RESO 32
#define CC_FILTER_ENV_DEPTH 33
#define CC_LFO2_FILTER_DEPTH 34

#define CC_AMP_ENV_ATTACK 35
#define CC_AMP_ENV_DECAY 36
#define CC_AMP_ENV_SUSTAIN 37
#define CC_AMP_ENV_RELEASE 38

#define CC_FILTER_ENV_ATTACK 39
#define CC_FILTER_ENV_DECAY 40
#define CC_FILTER_ENV_SUSTAIN 41
#define CC_FILTER_ENV_RELEASE 42

#define CC_DELAY_TIME 43
#define CC_DELAY_FEEDBACK 44
#define CC_DELAY_TONE 45
#define CC_DELAY_MIX 46

#define CC_REVERB_ROOMSIZE 47
#define CC_REVERB_DAMPING 48
#define CC_REVERB_INPUTFILTER 49
#define CC_REVERB_MIX 50

/* Uncomment for debug mode (prints debug info via serial) */
#define DEBUG_MODE 1

/* DIN MIDI */
#define MIDI_CHANNEL 1 //seb hard-coded for now

/* USB MIDI */
#define MIDI_DEVICE_USB 1
#ifdef MIDI_DEVICE_USB
#define USBCON 1
#endif

/* Various */
#define SD_CS_PIN BUILTIN_SDCARD //10
#define NUM_PRESETS 16
#define NUM_SYNTH_PARAMS 64 // currently less, but reserve 64 values in preset
#define NUM_VOICES 4
#define NUM_WAVEFORMS 4
#define NUM_LFO_WAVEFORMS 4

/* Buttons, encoder */
#define BUTTON1_PIN 3
#define BUTTON2_PIN 4
#define BUTTON3_PIN 5
#define BUTTON4_PIN 8
#define ENCODER_SW_PIN 20
#define ENCODER_PIN1 21
#define ENCODER_PIN2 24
#define DEBOUNCE_MS 10

/* Hardware controls */
#define NUM_SWITCHES 5 // Including encoder switch
#define NUM_POTS 8
#define NUM_LAYERS 8
#define NUM_CONTROLS (NUM_POTS * NUM_LAYERS)
#define MOV_AVG 8
