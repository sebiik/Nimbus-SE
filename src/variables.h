// Create LCD instance
hd44780_I2Clcd lcd;

// Create DIN MIDI instance
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

/* Encoder variables */
volatile int lastEncoded = 0;
volatile long encoderValue = 0;
int scaledEncVal;
int prevScaledEncVal;

/* MIDI 'multiply by 1/127' helper */
const float DIV127 = (1.0 / 127.0);

/* Buttons, encoder switch */
Bounce btnSwBouncers[NUM_SWITCHES] = {
  Bounce(BUTTON1_PIN, DEBOUNCE_MS),
  Bounce(BUTTON2_PIN, DEBOUNCE_MS),
  Bounce(BUTTON3_PIN, DEBOUNCE_MS),
  Bounce(BUTTON4_PIN, DEBOUNCE_MS),
  Bounce(ENCODER_SW_PIN, DEBOUNCE_MS),
};
const uint8_t btnSwPins[NUM_SWITCHES] = {
  BUTTON1_PIN,
  BUTTON2_PIN,
  BUTTON3_PIN,
  BUTTON4_PIN,
  ENCODER_SW_PIN
};

/* Unknown */
uint8_t   menuCount;
int   encoded;
unsigned long clearTimeStamp;

//preset stuff
uint8_t presetNumber = -1;
File    myFile;
const String fileNames[NUM_PRESETS] = {"00.TXT","01.TXT","02.TXT","03.TXT",
                                       "04.TXT","05.TXT","06.TXT","07.TXT",
                                       "08.TXT","09.TXT","10.TXT","11.TXT",
                                       "12.TXT","13.TXT","14.TXT","15.TXT"};

// Amp, peak values
float finalAmp;
float voiceAPeak;
float voiceBPeak;
float voiceCPeak;
float voiceDPeak;

float frequency;
// int   ampAttackTime = 10;
// int   ampDecayTime = 10;
// int   ampSustainLevel = 1;
// int   ampReleaseTime = 10;

bool isActiveEnvA;
bool isActiveEnvB;
bool isActiveEnvC;
bool isActiveEnvD;

float lfo1Freq = 1;
float lfo2Freq = 1;
float lfo1PitchDepth;
float lfo2FilterDepth;

float pitchMod = 1;
const float octaves[4] = {.5,1,1.5,2};
uint8_t   octaveOsc1;
uint8_t   octaveOsc2;
uint8_t   octaveOsc3;
int   filterFreq = 1000;
float filterRes;
float filterEnvDepth;

float masterDetune;
float plusDetune;
float minusDetune;
unsigned long filterEnvAttackTime = 10;
unsigned long filterEnvDecayTime = 10;
unsigned long filterEnvSustainLevel = 1;
unsigned long filterEnvReleaseTime = 10;

float voices[NUM_VOICES];
float voiceFreqs[NUM_VOICES];
float voiceVels[NUM_VOICES];
float voiceMod;

float   ampArray[NUM_VOICES];
uint8_t voiceNum;

/* ADC, button variables */
const uint8_t ainPinList[12] = {1, 2, 3, 6, 7, 16, 17, 18, 19, 20, 21, 22};
const float EMA_a = 0.125;      //initialize EMA alpha

uint8_t ADCcounter = 0;
uint8_t activeLayer = 0;
uint8_t controls[NUM_CONTROLS];
uint8_t controlsLast[NUM_CONTROLS];
bool  paramLocks[NUM_CONTROLS];
float   ainRead[NUM_POTS];
