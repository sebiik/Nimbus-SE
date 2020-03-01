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
#define NUM_SWITCHES 5 // Including encoder switch
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

/* ADC channels */
#define NUM_POTS 8
#define NUM_LAYERS 4
#define NUM_CONTROLS (NUM_POTS * NUM_LAYERS)
#define MOV_AVG 8
