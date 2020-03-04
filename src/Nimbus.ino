/* Original includes */
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <Metro.h>

/* Additional includes */
#include <MIDI.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Clcd.h>
#include "GUITool.h"
#include "defines.h"
#include "variables.h"


/***************************** Setup ***************************/
void setup() {
  #include "voiceStatic.h"

  /* Initialize LCD */
  lcd.begin(16, 2);
  lcd.noBlink();
  lcd.noCursor();
  lcd.backlight();
  lcd.noAutoscroll();
  lcd.lineWrap();
  lcd.display();
  lcd.home();
  /* Welcome message */
  lcd.write("   Nimbus SE    ");
  lcd.write("Otem, sebiiksbcs");
  delay(1000);
  lcd.clear();

  /* Initialize audio codec */
  AudioMemory(64);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.8);

  /* Initialize serial connection */
  Serial.begin(9600);

  /* Initialize MIDI */
  MIDI.begin(MIDI_CHANNEL);
  MIDI.setHandleNoteOn(OnNoteOn);
  MIDI.setHandleNoteOff(OnNoteOff);
  MIDI.setHandleControlChange(OnControlChange);
  MIDI.setHandleProgramChange(OnProgramChange);
  #ifdef MIDI_DEVICE_USB
  usbMIDI.begin();
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleControlChange(OnControlChange);
  usbMIDI.setHandleProgramChange(OnProgramChange);
  #endif

  /* Initialize SD */
  initSD();

  /* Initialize ADC */
  // initADC();

  /* Initialize encoder */
  pinMode(ENCODER_PIN1, INPUT);
  pinMode(ENCODER_PIN2, INPUT);
  digitalWrite(ENCODER_PIN1, HIGH);
  digitalWrite(ENCODER_PIN2, HIGH);
  attachInterrupt(ENCODER_PIN1, updateEncoder, CHANGE);
  attachInterrupt(ENCODER_PIN2, updateEncoder, CHANGE);

  /*Initialize switches, encoderBtn */
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);
  pinMode(ENCODER_SW_PIN, INPUT_PULLUP);

  /* Test preset load and save */
  setSynthParam(CC_OSC1_VOLUME, 127);
  setSynthParam(CC_OSC2_VOLUME, 63);
  setSynthParam(CC_OSC3_VOLUME, 0);
  setSynthParam(CC_NOISE_VOLUME, 0);

  setSynthParam(CC_OSC1_SHAPE, 2);
  setSynthParam(CC_OSC2_SHAPE, 2);
  setSynthParam(CC_OSC3_SHAPE, 0);
  setSynthParam(CC_DETUNE, 8);

  setSynthParam(CC_OSC1_OCTAVE, 1);
  setSynthParam(CC_OSC2_OCTAVE, 1);
  setSynthParam(CC_OSC3_OCTAVE, 1);
  setSynthParam(CC_LFO1_PITCH_DEPTH, 0);

  setSynthParam(CC_LFO1_SHAPE, 0);
  setSynthParam(CC_LFO1_FREQ, 32);
  setSynthParam(CC_LFO1_, 0);
  setSynthParam(CC_LFO1__, 0);
  // TODO pseudo noise filter param?

  setSynthParam(CC_LFO2_SHAPE, 1);
  setSynthParam(CC_LFO2_FREQ, 32);
  setSynthParam(CC_LFO2_, 0);
  setSynthParam(CC_LFO2__, 0);

  setSynthParam(CC_FILTER_FREQ, 31);
  setSynthParam(CC_FILTER_RESO, 0);
  setSynthParam(CC_FILTER_ENV_DEPTH, 63);
  setSynthParam(CC_LFO2_FILTER_DEPTH, 0);

  setSynthParam(CC_AMP_ENV_ATTACK, 0);
  setSynthParam(CC_AMP_ENV_DECAY, 16);
  setSynthParam(CC_AMP_ENV_SUSTAIN, 127);
  setSynthParam(CC_AMP_ENV_RELEASE, 16);

  setSynthParam(CC_FILTER_ENV_ATTACK, 0);
  setSynthParam(CC_FILTER_ENV_DECAY, 32);
  setSynthParam(CC_FILTER_ENV_SUSTAIN, 0);
  setSynthParam(CC_FILTER_ENV_RELEASE, 16);

  setSynthParam(CC_DELAY_TIME, 127);
  setSynthParam(CC_DELAY_FEEDBACK, 127);
  setSynthParam(CC_DELAY_TONE, 63);
  setSynthParam(CC_DELAY_MIX, 63);

  setSynthParam(CC_REVERB_ROOMSIZE, 0);
  setSynthParam(CC_REVERB_DAMPING, 0);
  setSynthParam(CC_REVERB_INPUTFILTER, 0);
  setSynthParam(CC_REVERB_MIX, 0);

  for (int p=51; p<64; p++){
    setSynthParam(p, 0);
  }

}


/*************************** Main loop *************************/
void loop() {

  /* Read MIDI */
  MIDI.read();
  #ifdef MIDI_DEVICE_USB
  usbMIDI.read();
  #endif

  /* Read encoder */ // TODO: currently no function
  if (abs(scaledEncVal - prevScaledEncVal) > 0) {
    // ...
    prevScaledEncVal = scaledEncVal;
  }

  /* Read pot values */
  if (ADCcounter % 16 == 0) {
    // readADC();
    updateCC();
  }
  ADCcounter++;

  /* Buttons, encoder switch */
  for (uint8_t i = 0; i < NUM_SWITCHES; i++) {
    if (btnSwBouncers[i].update()) {
      if (btnSwBouncers[i].risingEdge()) {
        switch (i) {
          case 0 ... 3:
          // switch layers directly
          activeLayer = i; // TODO set respective LED
          break;
          case 4: // TODO encoder switch...or remove entirely
          if (!digitalRead(btnSwPins[i])) {
            clearTimeStamp = millis();

            menuCount++;
            menuCount %= 4;

            if (menuCount == 4) { }
            else { }
          }
          break;
        }
      }
    }
  }

  /* Handle poly voices */
  for (uint8_t v = 0; v < NUM_VOICES; v++) {
    switch(v) {

      case 0: {
        //VoiceA
        oscOneA.frequency(voiceFreqs[v] * octaves[octaveOsc1] * pitchMod);
        oscTwoA.frequency(voiceFreqs[v] * octaves[octaveOsc2] * plusDetune);
        oscThreeA.frequency(voiceFreqs[v] * octaves[octaveOsc3] * minusDetune);
        //Env
        if(voices[v]) {
          if (!isActiveEnvA) {
            ampEnvA.noteOn();
            filterEnvA.noteOn();
            isActiveEnvA = true;
          }
        }
        else {
          ampEnvA.noteOff();
          filterEnvA.noteOff();
          isActiveEnvA = false;
        }
        break;
      }

      case 1: {
        //VoiceB
        oscOneB.frequency(voiceFreqs[v] * octaves[octaveOsc1]);
        oscTwoB.frequency(voiceFreqs[v] * octaves[octaveOsc2] * plusDetune);
        oscThreeB.frequency(voiceFreqs[v] * octaves[octaveOsc3] * minusDetune);
        //Env
        if(voices[v]) {
          if (!isActiveEnvB) {
            ampEnvB.noteOn();
            filterEnvB.noteOn();
            isActiveEnvB = true;
          }
        }
        else {
          ampEnvB.noteOff();
          filterEnvB.noteOff();
          isActiveEnvB = false;
        }
        break;
      }

      case 2: {
        //VoiceC
        oscOneC.frequency(voiceFreqs[v] * octaves[octaveOsc1]);
        oscTwoC.frequency(voiceFreqs[v] * octaves[octaveOsc2] * plusDetune);
        oscThreeC.frequency(voiceFreqs[v] * octaves[octaveOsc3] * minusDetune);
        //Env
        if(voices[v]) {
          if (!isActiveEnvC) {
            ampEnvC.noteOn();
            filterEnvC.noteOn();
            isActiveEnvC = true;
          }
        }
        else {
          ampEnvC.noteOff();
          filterEnvC.noteOff();
          isActiveEnvC = false;
        }
        break;
      }

      case 3: {
        //VoiceD
        oscOneD.frequency(voiceFreqs[v] * octaves[octaveOsc1]);
        oscTwoD.frequency(voiceFreqs[v] * octaves[octaveOsc2] * plusDetune);
        oscThreeD.frequency(voiceFreqs[v] * octaves[octaveOsc3] * minusDetune);
        //Env
        if(voices[v]) {
          if (!isActiveEnvD) {
            ampEnvD.noteOn();
            filterEnvD.noteOn();
            isActiveEnvD = true;
          }
        }
        else {
          ampEnvD.noteOff();
          filterEnvD.noteOff();
          isActiveEnvD = false;
        }
        break;
      }
    }
  }

  /* Update LFOs*/
  lfo1.frequency(lfo1Freq);
  lfo2.frequency(lfo2Freq);

  /* Update filter */
  filterA.frequency(filterFreq);
  filterB.frequency(filterFreq);
  filterC.frequency(filterFreq);
  filterD.frequency(filterFreq);
  filterA.resonance(filterRes);
  filterB.resonance(filterRes);
  filterC.resonance(filterRes);
  filterD.resonance(filterRes);
  filterModMixerA.gain(0, filterEnvDepth);
  filterModMixerB.gain(0, filterEnvDepth);
  filterModMixerC.gain(0, filterEnvDepth);
  filterModMixerD.gain(0, filterEnvDepth);
  filterModMixerA.gain(1, lfo2FilterDepth);
  filterModMixerB.gain(1, lfo2FilterDepth);
  filterModMixerC.gain(1, lfo2FilterDepth);
  filterModMixerD.gain(1, lfo2FilterDepth);

  /* Update pitch mod */
  pitchModMixerA.gain(0, 0); // TODO pitch env mod
  pitchModMixerB.gain(0, 0);
  pitchModMixerC.gain(0, 0);
  pitchModMixerD.gain(0, 0);
  pitchModMixerA.gain(1, lfo1PitchDepth);
  pitchModMixerB.gain(1, lfo1PitchDepth);
  pitchModMixerC.gain(1, lfo1PitchDepth);
  pitchModMixerD.gain(1, lfo1PitchDepth);


  /* Voice peak analyzers */
  if (peakA.available()) {
    voiceAPeak = peakA.read();
    ampArray[0] = voiceAPeak;
  }
  if (peakB.available()) {
    voiceBPeak = peakB.read();
    ampArray[1] = voiceBPeak;
  }
  if (peakC.available()) {
    voiceCPeak = peakC.read();
    ampArray[2] = voiceCPeak;
  }
  if (peakD.available()) {
    voiceDPeak = peakD.read();
    ampArray[3] = voiceDPeak;
  }
  /* Final peak analyzer */
  if (finalPeak.available()) {
    finalAmp = finalPeak.read();
  }
}

/* Init SD function */
void initSD(void) {
  SPI.setMOSI(7);  // Audio shield has MOSI on pin 7
  SPI.setSCK(14);  // Audio shield has SCK on pin 14
  #ifdef DEBUG_MODE
  Serial.print("Initializing SD card...");
  #endif
  if (!SD.begin(SD_CS_PIN)) {
    #ifdef DEBUG_MODE
    Serial.println("SD init failed!");
    #endif
    lcd.clear();
    lcd.write("SD init failed!");
    return;
  }
  #ifdef DEBUG_MODE
  Serial.println("SD card found");
  #endif
  lcd.clear();
  lcd.write("SD card found.");
}

/* ADC, button read functions */
void initADC(void) {
  for (uint8_t i = 0; i < NUM_LAYERS; i++) {
    for (uint8_t j = 0; j < NUM_POTS; j++) {
      controlsLast[i*NUM_POTS + j] = controls[i*NUM_POTS + j];
    }
  }
}

void readADC(void) {
  // Loop through ADC channels
  for (uint8_t i = 0; i < NUM_POTS; i++) {
    // Moving Average
    float sensorValues[MOV_AVG];
    float sensorAverage = 0;
    for (uint8_t j = 0; j < MOV_AVG; j++) {
      sensorValues[j] = analogRead(ainPinList[i]);
      sensorAverage += sensorValues[j] * 0.125;
    }
    sensorAverage = round(map(sensorAverage, 3.0, 1018.0, 0.0, 127.0));
    // If value exceeds threshold, update
    if ((abs(sensorAverage - ainRead[i]) > 0.9)) {
      ainRead[i] += EMA_a * (sensorAverage - ainRead[i]);
      controls[activeLayer*NUM_POTS + i] = uint8_t(ainRead[i]);
    }
  }
}

void sendCC(uint8_t paramNumber, uint8_t ccValue, uint8_t outChannel) {
  MIDI.sendControlChange(paramNumber, ccValue, outChannel);
  #ifdef MIDI_DEVICE_USB
  usbMIDI.sendControlChange(paramNumber, ccValue, outChannel);
  #endif

}

void updateCC(void) {
  for (uint8_t i=0; i<NUM_LAYERS; i++) {
    for (uint8_t j=0; j<NUM_POTS; j++) {
      if (controls[i*NUM_POTS + j] != controlsLast[i*NUM_POTS + j]) {
        sendCC(i*NUM_POTS + j+11,  controls[i*NUM_POTS + j], MIDI_CHANNEL);
        setSynthParam(i*NUM_POTS + j+11,  controls[i*NUM_POTS + j]);
        controlsLast[i * NUM_POTS + j] = controls[i * NUM_POTS + j];
      }
    }
  }
}


/* MIDI functions */
void OnNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (note >= 108) {
      savePreset(note - 108);
      lcd.clear();
      lcd.write("Saved "); lcd.print(fileNames[note-108]);
  }
  else {
    float freq = 440.0 * powf(2.0, (float)(note - 69) * 0.08333333);
    float vel = (float)velocity * DIV127;
    startVoice(freq, vel);
  }
}

void OnNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  float freq = 440.0 * powf(2.0, (float)(note - 69) * 0.08333333);
  endVoice(freq);
}

void OnControlChange(uint8_t channel, uint8_t control, uint8_t value) {
  setSynthParam(control, value);
  controls[control-11] = value;
  paramLocks[control-11] = true; //TODO parameter locks
  lcd.clear(); lcd.write("ControlC: ");
  lcd.write("chn:"); lcd.print(channel); lcd.write(" ");
  lcd.write("cc#:"); lcd.print(control); lcd.write(" ");
  lcd.write("val:"); lcd.print(value);
}

void OnProgramChange(uint8_t channel, uint8_t value) {
  loadPreset(value);
}


/* Note functions */
void startVoice(float frequency, float velocity) {
  for (int i = 0; i < NUM_VOICES; i++) {
    if (!voices[i]) {
      voices[i] = frequency;
      voiceFreqs[i] = frequency;
      voiceVels[i] = velocity;
      if (voices[i]) {
        return;
      }
    }
  }

  voiceNum = lowestAmp();
  //if voice is already in use scan to next voice
  for (int i = 0; i < NUM_VOICES; i++) {
    if (voices[voiceNum]) {
      voiceNum++;
      if (voiceNum > 3) {
        voiceNum = 0;
      }
    }
  }
  //Assign (unused voice || lowest voice)
  voices[voiceNum] = frequency;
  voiceFreqs[voiceNum] = voices[voiceNum];
  voiceVels[voiceNum] = velocity;

}

void endVoice(float frequency) {
  for (int i = 0; i < NUM_VOICES; i++) {
    if(voiceFreqs[i] == frequency) {
      voices[i] = 0;
    }
  }
}

int lowestAmp(void) {
  int index = 0;
  for (int i = 0; i < NUM_VOICES; i++) {
    if (ampArray[i] < ampArray[index]) {
      index = i;
    }
  }
  return index;
}


/* Preset functions */
void loadPreset(uint8_t number) {
  String currentPreset = fileNames[number];

  myFile = SD.open(currentPreset.c_str());

  if (myFile) {
    for (uint8_t p = 0; p < NUM_SYNTH_PARAMS; p++) {
      int input = myFile.parseFloat();
      controls[p] = input;
      paramLocks[p] = true;
    }
    myFile.close();
    lcd.clear(); lcd.write("Loaded "); lcd.print(currentPreset);
    for (uint8_t c = 0; c < NUM_SYNTH_PARAMS; c++) {
      setSynthParam(c+11, controls[c]);
    }
    presetNumber = number;
  } else {
    #ifdef DEBUG_MODE
    Serial.println("error opening file");
    #endif
    lcd.clear(); lcd.write("Error loading preset "); lcd.print(currentPreset);
  }
}

void savePreset(uint8_t number) {
  String currentPreset = fileNames[number];
  // Remove File
  if (SD.exists(currentPreset.c_str())) {
    #ifdef DEBUG_MODE
    Serial.println("remove the file");
    #endif
    SD.remove(currentPreset.c_str());
  }
  // Open File
  myFile = SD.open(currentPreset.c_str(), FILE_WRITE);
  //if the file opened okay, write to it:
  if (myFile) {
    for (uint8_t i = 0; i<NUM_SYNTH_PARAMS; i++) {
      myFile.println(controls[i]);
    }
    myFile.close();
    lcd.clear(); lcd.write("Saved "); lcd.print(currentPreset);
    #ifdef DEBUG_MODE
    Serial.print("wrote to file");
    #endif
  } else {
    // if the file didn't open, print an error:
    lcd.clear(); lcd.write("Error saving    "); lcd.print(currentPreset);
    #ifdef DEBUG_MODE
    Serial.println("error opening file");
    #endif
  }
}


/* Voice edit functions */ // TODO PWM
void setOsc1Shape(uint8_t wave) {
  wave %= NUM_WAVEFORMS;
  switch(wave) {
    case 0:
    oscOneA.begin(WAVEFORM_SAWTOOTH);
    oscOneB.begin(WAVEFORM_SAWTOOTH);
    oscOneC.begin(WAVEFORM_SAWTOOTH);
    oscOneD.begin(WAVEFORM_SAWTOOTH);
    break;

    case 1:
    oscOneA.begin(WAVEFORM_SQUARE);
    oscOneB.begin(WAVEFORM_SQUARE);
    oscOneC.begin(WAVEFORM_SQUARE);
    oscOneD.begin(WAVEFORM_SQUARE);
    break;

    case 2:
    oscOneA.begin(WAVEFORM_PULSE);
    oscOneB.begin(WAVEFORM_PULSE);
    oscOneC.begin(WAVEFORM_PULSE);
    oscOneD.begin(WAVEFORM_PULSE);
    break;

    case 3:
    oscOneA.begin(WAVEFORM_TRIANGLE);
    oscOneB.begin(WAVEFORM_TRIANGLE);
    oscOneC.begin(WAVEFORM_TRIANGLE);
    oscOneD.begin(WAVEFORM_TRIANGLE);
    break;

  }
}

void setOsc2Shape(uint8_t wave) {
  wave %= NUM_WAVEFORMS;
  switch(wave) {
    case 0:
    oscTwoA.begin(WAVEFORM_SAWTOOTH);
    oscTwoB.begin(WAVEFORM_SAWTOOTH);
    oscTwoC.begin(WAVEFORM_SAWTOOTH);
    oscTwoD.begin(WAVEFORM_SAWTOOTH);
    break;

    case 1:
    oscTwoA.begin(WAVEFORM_SQUARE);
    oscTwoB.begin(WAVEFORM_SQUARE);
    oscTwoC.begin(WAVEFORM_SQUARE);
    oscTwoD.begin(WAVEFORM_SQUARE);
    break;

    case 2:
    oscTwoA.begin(WAVEFORM_PULSE);
    oscTwoB.begin(WAVEFORM_PULSE);
    oscTwoC.begin(WAVEFORM_PULSE);
    oscTwoD.begin(WAVEFORM_PULSE);
    break;

    case 3:
    oscTwoA.begin(WAVEFORM_TRIANGLE);
    oscTwoB.begin(WAVEFORM_TRIANGLE);
    oscTwoC.begin(WAVEFORM_TRIANGLE);
    oscTwoD.begin(WAVEFORM_TRIANGLE);
    break;
  }
}

void setOsc3Shape(uint8_t wave) {
  wave %= NUM_WAVEFORMS;
  switch(wave) {

    case 0:
    oscThreeA.begin(WAVEFORM_SAWTOOTH);
    oscThreeB.begin(WAVEFORM_SAWTOOTH);
    oscThreeC.begin(WAVEFORM_SAWTOOTH);
    oscThreeD.begin(WAVEFORM_SAWTOOTH);
    break;

    case 1:
    oscThreeA.begin(WAVEFORM_SQUARE);
    oscThreeB.begin(WAVEFORM_SQUARE);
    oscThreeC.begin(WAVEFORM_SQUARE);
    oscThreeD.begin(WAVEFORM_SQUARE);
    break;

    case 2:
    oscThreeA.begin(WAVEFORM_PULSE);
    oscThreeB.begin(WAVEFORM_PULSE);
    oscThreeC.begin(WAVEFORM_PULSE);
    oscThreeD.begin(WAVEFORM_PULSE);
    break;

    case 3:
    oscThreeA.begin(WAVEFORM_TRIANGLE);
    oscThreeB.begin(WAVEFORM_TRIANGLE);
    oscThreeC.begin(WAVEFORM_TRIANGLE);
    oscThreeD.begin(WAVEFORM_TRIANGLE);
    break;
  }
}

void setLfo1Shape(uint8_t wave) {
  wave %= NUM_LFO_WAVEFORMS;
  switch(wave) {

    case 0:
    lfo1.begin(WAVEFORM_SINE);
    break;

    case 1:
    lfo1.begin(WAVEFORM_SAWTOOTH_REVERSE);
    break;

    case 2:
    lfo1.begin(WAVEFORM_SQUARE);
    break;

    case 3:
    lfo1.begin(WAVEFORM_SAMPLE_HOLD);
    break;
  }
}

void setLfo2Shape(uint8_t wave) {
  wave %= NUM_LFO_WAVEFORMS;
  switch(wave) {

    case 0:
    lfo2.begin(WAVEFORM_SINE);
    break;

    case 1:
    lfo2.begin(WAVEFORM_SAWTOOTH_REVERSE);
    break;

    case 2:
    lfo2.begin(WAVEFORM_SQUARE);
    break;

    case 3:
    lfo2.begin(WAVEFORM_SAMPLE_HOLD);
    break;
  }
}

void clearEverything(void) {
  menuCount = 0;
  presetNumber = -1;
  for (int i = 0; i < NUM_CONTROLS; i++) {
    paramLocks[i] = false;
  }
  for (int z = 0; z < NUM_VOICES; z++) {
    voices[z] = 0;
  }
}

void updateEncoder(void) {
  int MSB = digitalRead(ENCODER_PIN1); //MSB = most significant bit
  int LSB = digitalRead(ENCODER_PIN2); //LSB = least significant bit

  encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  if (encoderValue < 0) encoderValue = 0;
  scaledEncVal = encoderValue/4;
  lastEncoded = encoded; //store this value for next time
}

void setSynthParam(uint8_t number, uint8_t value) {
  controls[number-CC_OSC1_VOLUME] = value;
  controlsLast[number-CC_OSC1_VOLUME] = value;
  float valueNorm = value * DIV127;
  switch (number) {
    case CC_OSC1_VOLUME...CC_NOISE_VOLUME: {
      voiceMixerA.gain(number-11, valueNorm*0.25);
      voiceMixerB.gain(number-11, valueNorm*0.25);
      voiceMixerC.gain(number-11, valueNorm*0.25);
      voiceMixerD.gain(number-11, valueNorm*0.25);
      break;
    }

    case CC_OSC1_SHAPE: {
      setOsc1Shape(value);
      break;
    }

    case CC_OSC2_SHAPE: {
      setOsc2Shape(value);
      break;
    }

    case CC_OSC3_SHAPE: {
      setOsc3Shape(value);
      break;
    }

    case CC_DETUNE: {
      masterDetune = sq(valueNorm); // Detune
      plusDetune =  1 + masterDetune * 0.25;
      minusDetune = 1 - masterDetune * 0.125;
      break;
    }

    case CC_OSC1_OCTAVE: {
      octaveOsc1 = constrain(value, 0, 3);
      break;
    }

    case CC_OSC2_OCTAVE: {
      octaveOsc2 = constrain(value, 0, 3);
      break;
    }

    case CC_OSC3_OCTAVE: {
      octaveOsc3 = constrain(value, 0, 3);
      break;
    }

    case CC_LFO1_PITCH_DEPTH: {
      lfo1PitchDepth = sq(valueNorm);
      break;
    }

    case CC_LFO1_SHAPE: {
      setLfo1Shape(value);
      break;
    }

    case CC_LFO1_FREQ: {
      lfo1Freq = sq(valueNorm)*30; // lfo1 freq
      break;
    }

    case CC_LFO1_: {
      break;
    }

    case CC_LFO1__: {
      break;
    }

    case CC_LFO2_SHAPE: {
      setLfo2Shape(value);
      break;
    }

    case CC_LFO2_FREQ: {
      lfo2Freq = sq(valueNorm)*30; // lfo1 freq
      break;
    }

    case CC_LFO2_: {
      break;
    }

    case CC_LFO2__: {
      break;
    }

    case CC_FILTER_FREQ: {
      filterFreq = 40 + sq(valueNorm) * 16000; // Filter cutoff freq
      break;
    }

    case CC_FILTER_RESO: {
      filterRes = 0.7 + valueNorm * 4.3; // Filter resonance
      break;
    }

    case CC_FILTER_ENV_DEPTH: {
      filterEnvDepth = valueNorm;
      break;
    }

    case CC_LFO2_FILTER_DEPTH: {
      lfo2FilterDepth = valueNorm;
      break;
    }

    case CC_AMP_ENV_ATTACK: {
      float att = sq(valueNorm) * 11879.9 + 0.1;
      ampEnvA.attack(att);
      ampEnvB.attack(att);
      ampEnvC.attack(att);
      ampEnvD.attack(att);
      break;
    }

    case CC_AMP_ENV_DECAY: {
      float dec = sq(valueNorm) * 11879.9 + 0.1;
      ampEnvA.decay(dec);
      ampEnvB.decay(dec);
      ampEnvC.decay(dec);
      ampEnvD.decay(dec);
      break;
    }

    case CC_AMP_ENV_SUSTAIN: {
      ampEnvA.sustain(valueNorm);
      ampEnvB.sustain(valueNorm);
      ampEnvC.sustain(valueNorm);
      ampEnvD.sustain(valueNorm);
      break;
    }

    case CC_AMP_ENV_RELEASE: {
      float rel = sq(valueNorm) * 11879.9 + 0.1;
      ampEnvA.release(rel);
      ampEnvB.release(rel);
      ampEnvC.release(rel);
      ampEnvD.release(rel);
      break;
    }

    case CC_FILTER_ENV_ATTACK: {
      float att = sq(valueNorm) * 11879.9 + 0.1;
      filterEnvA.attack(att);
      filterEnvB.attack(att);
      filterEnvC.attack(att);
      filterEnvD.attack(att);
      break;
    }

    case CC_FILTER_ENV_DECAY: {
      float dec = sq(valueNorm) * 11879.9 + 0.1;
      filterEnvA.decay(dec);
      filterEnvB.decay(dec);
      filterEnvC.decay(dec);
      filterEnvD.decay(dec);
      break;
    }

    case CC_FILTER_ENV_SUSTAIN: {
      filterEnvA.sustain(valueNorm);
      filterEnvB.sustain(valueNorm);
      filterEnvC.sustain(valueNorm);
      filterEnvD.sustain(valueNorm);
      break;
    }

    case CC_FILTER_ENV_RELEASE: {
      float rel = sq(valueNorm) * 11879.9 + 0.1;
      filterEnvA.release(rel);
      filterEnvB.release(rel);
      filterEnvC.release(rel);
      filterEnvD.release(rel);
      break;
    }

    case CC_DELAY_TIME: {
      delay1.delay(0, sq(valueNorm) * 1499 + 1); // Delay time
      break;
    }

    case CC_DELAY_FEEDBACK: {
      delayFbMixer.gain(1, valueNorm * 0.862); // Delay feedback
      break;
    }

    case CC_DELAY_TONE: {
      delayFilter.frequency(80 + sq(valueNorm) * 10000);
      // delayFilter.setLowpass(1, 80 + sq(valueNorm) * 10000, 1.0); // TODO setBandpass etc.
      break;
    }

    case CC_DELAY_MIX: {
      delayMixer.gain(1, valueNorm); // Delay mix
      break;
    }

    case CC_REVERB_ROOMSIZE: {
      freeverbs.roomsize(valueNorm); // Reverb size
      break;
    }

    case CC_REVERB_DAMPING: {
      freeverbs.damping(valueNorm); // Reverb damping
      break;
    }

    case CC_REVERB_INPUTFILTER: {
      reverbInputFilter.frequency(20 + sq(valueNorm)*3000);
      // reverbInputFilter.setHighpass(0, 20 + sq(valueNorm)*3000, 0.7);
      break;
    }

    case CC_REVERB_MIX: {
      reverbMixerL.gain(1, valueNorm); // Reverb mix
      reverbMixerR.gain(1, valueNorm);
      break;
    }
  }
}
