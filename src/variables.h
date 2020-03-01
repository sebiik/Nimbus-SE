// LCD
hd44780_I2Clcd lcd;

// DIN MIDI
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

volatile int lastEncoded = 0;
volatile long encoderValue = 0;
int scaledEncVal;
int prevScaledEncVal;

// MIDI 'divide by 127' helper
const float DIV127 = (1.0 / 127.0);

// Buttons, encoder switch
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

uint8_t   menuCount;
int   encoded;
unsigned long clearTimeStamp;

//preset stuff
uint8_t presetNumber = -1;
File    myFile;
const String fileNames[16] = {"00.TXT","01.TXT","02.TXT","03.TXT",
                              "04.TXT","05.TXT","06.TXT","07.TXT",
                              "08.TXT","09.TXT","10.TXT","11.TXT",
                              "12.TXT","13.TXT","14.TXT","15.TXT"};

//Synth Params
float finalAmp;
float voiceAPeak;
float voiceBPeak;
float voiceCPeak;
float voiceDPeak;

float frequency;
int   attackTime = 10;
int   releaseTime = 10;
float lfo1Amt;
float lfo1Freq;
int   lfoIndex;
float lfoPitchMod;
const int   lfoTimeMathArray[5] = {250, 500, 1000, 2000, 4000};
const float octave[4] = {.25,.5,1,2};
const int   midiOctave[4] = {-24, -12, 0, 12};
int   octaveKey;
int   filterFreq = 1000;
float filterRes;
float masterDetune;
float plusDetune;
float minusDetune;
unsigned long filterEnvAttackTime;
unsigned long filterEnvReleaseTime;

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
