/* Original includes */
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <Metro.h>

/* Seb additional includes */
#include <MIDI.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Clcd.h>
#include "GUITool.h"
#include "defines.h"
#include "variables.h"


/***************************** Setup ***************************/
void setup() {

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

  /* Initialize ADC */
  initADC();

  /* Initialize static values */
  for (uint8_t g=0; g<4; g++) { polyMixer.gain(g,0.25); }
  // polyMixer.gain(0,.25);
  // polyMixer.gain(1,.25);
  // polyMixer.gain(2,.25);
  // polyMixer.gain(3,.25);
  oscOneA.amplitude(.25);
  oscOneB.amplitude(.25);
  oscOneC.amplitude(.25);
  oscOneD.amplitude(.25);
  oscTwoA.amplitude(.25);
  oscTwoB.amplitude(.25);
  oscTwoC.amplitude(.25);
  oscTwoD.amplitude(.25);
  oscThreeA.amplitude(.25);
  oscThreeB.amplitude(.25);
  oscThreeC.amplitude(.25);
  oscThreeD.amplitude(.25);
  filterA.octaveControl(2.5);
  filterB.octaveControl(2.5);
  filterC.octaveControl(2.5);
  filterD.octaveControl(2.5);
  delayFilter1.setHighpass(0, 80, 0.7);
  delayMixer.gain(0, 1);
  delayFbMixer.gain(0, 1.0);
  delayFbMixer.gain(1, 0.85);
  reverbMixerL.gain(0, 1);
  reverbMixerR.gain(0, 1);

  lfo1.begin(.7,.5,WAVEFORM_SINE);
  lfo1.amplitude(1);
  lfo1.frequency(1);

  lfo1.begin(.7,.5,WAVEFORM_SINE);
  lfo1.amplitude(1);
  lfo1.frequency(1);

  /* Test reverb */
  reverbInputFilter.setHighpass(0, 80, 0.7); // stage(0-3), frequency, resonance
  freeverbs1.roomsize(0.98);
  freeverbs1.damping(0.25);
  /* Reverb wet mix */
  reverbMixerL.gain(1, 0.25);
  reverbMixerR.gain(1, 0.25);

  //
  setSynthParam(11,127);
  setSynthParam(12,9);
  setSynthParam(13,0);
  setSynthParam(14,1);
  setSynthParam(15,0);
  setSynthParam(16,63);
  setSynthParam(17,0);
  setSynthParam(18,63);
  setSynthParam(19,127);
  setSynthParam(20,1);
  setSynthParam(21,1);
  setSynthParam(22,1);
  setSynthParam(23,1);
  setSynthParam(24,127);
  setSynthParam(25,63);
  setSynthParam(26,0);
  setSynthParam(27,0);
  setSynthParam(28,0);
  setSynthParam(29,0);
  setSynthParam(30,0);
  setSynthParam(31,0);
  setSynthParam(32,0);
  setSynthParam(33,0);
  setSynthParam(34,0);

  /* Initialize encoder */
  // pinMode(ENCODER_PIN1, INPUT);
  // pinMode(ENCODER_PIN2, INPUT);
  // digitalWrite(ENCODER_PIN1, HIGH);
  // digitalWrite(ENCODER_PIN2, HIGH);
  // attachInterrupt(ENCODER_PIN1, updateEncoder, CHANGE);
  // attachInterrupt(ENCODER_PIN2, updateEncoder, CHANGE);

  /*Initialize switches, encoderBtn */
  // pinMode(BUTTON1_PIN, INPUT_PULLUP);
  // pinMode(BUTTON2_PIN, INPUT_PULLUP);
  // pinMode(BUTTON3_PIN, INPUT_PULLUP);
  // pinMode(BUTTON4_PIN, INPUT_PULLUP);
  // pinMode(ENCODER_SW_PIN, INPUT_PULLUP);

  /* Initialize switch values */
  // for (int i = 0; i < NUM_SWITCHES; ++i) {
  //   if (i<4) {
  //     rawVals[i + 16] = digitalRead(btnSwPins[i]);
  //   }
  //   switch (i) {
  //     case 0:
  //     setOsc1Shape(digitalRead(btnSwPins[i]));
  //     break;
  //     case 1:
  //     setOsc2Shape(digitalRead(btnSwPins[i]));
  //     break;
  //     case 2:
  //     setOsc3Shape(digitalRead(btnSwPins[i]));
  //     break;
  //     case 3:
  //     setLfoShape(digitalRead(btnSwPins[i]));
  //     break;
  //     case 4:
  //     if (!digitalRead(btnSwPins[i])) {// TODO: encoder switch isn't really used ATM
  //       clearTimeStamp = millis();
  //
  //       menuCount++;
  //       if (menuCount > 4) {
  //         menuCount = 0;
  //         // checkSeqStart();
  //       }
  //
  //       if (menuCount == 4) {
  //         // seqRunning = false;
  //         // seqEditMode = true;
  //       }
  //       else{
  //         // seqEditMode = false;
  //       }
  //     }
  //     break;
  //   }
  // }

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
    prevScaledEncVal = scaledEncVal;
  }

  /* Read pot values */
  if (ADCcounter % 16 == 0) {
    readADC();
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

              if (menuCount == 4) {
              }
              else { }
            }
          break;
        }
      }
    }
  }


  /* ClearEverything // long-press encoder switch for 2 sec clears everything? */
  // if ((abs(millis() - clearTimeStamp) > 2000) && !digitalRead(20)) {
  //   clearEverything();
  //   clearTimeStamp = millis();
  // }

  /* Handle poly voices */
  for (int i = 0; i < NUM_VOICES; ++i) {
    switch(i) {

      case 0: {
        //VoiceA
          oscOneA.frequency(voiceFreqs[i] * octave[octaveKey] * lfoPitchMod);
          oscTwoA.frequency(voiceFreqs[i] * octave[octaveKey] * plusDetune * lfoPitchMod);
          oscThreeA.frequency(voiceFreqs[i] * octave[octaveKey] * minusDetune * lfoPitchMod);
          //Env
          if(voices[i]) {
            ampEnvA.amplitude(voiceVels[i], attackTime);
            filterEnvA.amplitude(voiceVels[i],filterEnvAttackTime);
          }
          else {
            ampEnvA.amplitude(0, releaseTime);
            filterEnvA.amplitude(0,filterEnvReleaseTime);
          }
        break;
      }

      case 1: {
        //VoiceB
          oscOneB.frequency(voiceFreqs[i] * octave[octaveKey] * lfoPitchMod);
          oscTwoB.frequency(voiceFreqs[i] * octave[octaveKey] * plusDetune * lfoPitchMod);
          oscThreeB.frequency(voiceFreqs[i] * octave[octaveKey] * minusDetune * lfoPitchMod);
          //Env
          if(voices[i]) {
            ampEnvB.amplitude(voiceVels[i], attackTime);
            filterEnvB.amplitude(voiceVels[i],filterEnvAttackTime);
          }
          else {
            ampEnvB.amplitude(0, releaseTime);
            filterEnvB.amplitude(0,filterEnvReleaseTime);
          }
        break;
      }

      case 2: {
        //VoiceC
          oscOneC.frequency(voiceFreqs[i] * octave[octaveKey] * lfoPitchMod);
          oscTwoC.frequency(voiceFreqs[i] * octave[octaveKey] * plusDetune * lfoPitchMod);
          oscThreeC.frequency(voiceFreqs[i] * octave[octaveKey] * minusDetune * lfoPitchMod);
          //Env
          if(voices[i]) {
            ampEnvC.amplitude(voiceVels[i], attackTime);
            filterEnvC.amplitude(voiceVels[i],filterEnvAttackTime);
          }
          else {
            ampEnvC.amplitude(0, releaseTime);
            filterEnvC.amplitude(0,filterEnvReleaseTime);
          }
        break;
      }

      case 3: {
        //VoiceD
          oscOneD.frequency(voiceFreqs[i] * octave[octaveKey] * lfoPitchMod);
          oscTwoD.frequency(voiceFreqs[i] * octave[octaveKey] * plusDetune * lfoPitchMod);
          oscThreeD.frequency(voiceFreqs[i] * octave[octaveKey] * minusDetune * lfoPitchMod);
          //Env
          if(voices[i]) {
            ampEnvD.amplitude(voiceVels[i], attackTime);
            filterEnvD.amplitude(voiceVels[i],filterEnvAttackTime);
          }
          else {
            ampEnvD.amplitude(0, releaseTime);
            filterEnvD.amplitude(0,filterEnvReleaseTime);
          }
        break;
      }
    }
  }

  /* Update lfo values */
  lfo1.frequency(lfo1Freq);
  lfo1.amplitude(lfo1Amt);
  lfo2.frequency(lfo2Freq);
  lfo2.amplitude(lfo2Amt);

  /* Update filter values */
  filterA.frequency(filterFreq);
  filterB.frequency(filterFreq);
  filterC.frequency(filterFreq);
  filterD.frequency(filterFreq);
  filterA.resonance(filterRes);
  filterB.resonance(filterRes);
  filterC.resonance(filterRes);
  filterD.resonance(filterRes);

  //voiceA peak analyzer
  if (peakA.available()) {
    voiceAPeak = peakA.read();
    ampArray[0] = voiceAPeak;
  }
  //voiceB peak analyzer
  if (peakB.available()) {
    voiceBPeak = peakB.read();
     ampArray[1] = voiceBPeak;
  }
  //voiceC peak analyzer
  if (peakC.available()) {
    voiceCPeak = peakC.read();
    ampArray[2] = voiceCPeak;
  }
  //voiceD peak analyzer
  if (peakD.available()) {
    voiceDPeak = peakD.read();
    ampArray[3] = voiceDPeak;
  }
  //FinalPeak analyzer
  if (finalPeak.available()) {
    finalAmp = finalPeak.read();
  }

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
    loadPreset(note - 108);
    lcd.clear();
    lcd.write("Loaded "); lcd.print(fileNames[note-108]);

  }
  else {
    float freq = 440.0 * powf(2.0, (float)(note - 45) * 0.08333333);
    float vel = (float)velocity * DIV127;
    startVoice(freq, vel);
    lcd.clear(); lcd.write("Note on:  ");
    lcd.write("chn:"); lcd.print(channel); lcd.write(" ");
    lcd.write("nte:"); lcd.print(note); lcd.write(" ");
    lcd.write("vel:"); lcd.print(velocity);
  }
}

void OnNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  float freq = 440.0 * powf(2.0, (float)(note - 45) * 0.08333333);
  endVoice(freq);
  lcd.clear(); lcd.write("Note off: ");
  lcd.write("chn:"); lcd.print(channel); lcd.write(" ");
  lcd.write("nte:"); lcd.print(note); lcd.write(" ");
  lcd.write("vel:"); lcd.print(velocity);
}

void OnControlChange(uint8_t channel, uint8_t control, uint8_t value) {
  setSynthParam(control, value);
  controls[control] = value;
  paramLocks[control] = true;
  lcd.clear(); lcd.write("ControlC: ");
  lcd.write("chn:"); lcd.print(channel); lcd.write(" ");
  lcd.write("cc#:"); lcd.print(control); lcd.write(" ");
  lcd.write("val:"); lcd.print(value);
}

void OnProgramChange(uint8_t channel, uint8_t value) {
  //seb
  loadPreset(value);
}


/* Note functions */
void startVoice(float frequency, float velocity) {
  for (int i = 0; i < 4; ++i) {
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
  for (int i = 0; i < 4; ++i) {
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
  for (int i = 0; i < 4; ++i) {
    if(voiceFreqs[i] == frequency) {
      voices[i] = 0;
    }
  }
}

int lowestAmp() {
  int index = 0;
  for (int i = 0; i < 4; i++) {
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
    for (uint8_t i = 0; i < NUM_SYNTH_PARAMS; i++) {
      int input = myFile.parseFloat();
      controls[i] = input;
      paramLocks[i] = true;
    }
    myFile.close();
    lcd.clear(); lcd.write("Loaded "); lcd.print(currentPreset);
    for (uint8_t i = 0; i < NUM_SYNTH_PARAMS; i++) {
      setSynthParam(i+11, controls[i]);
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
    for (uint8_t i = 0; i < NUM_SYNTH_PARAMS; i++) {
      myFile.println(controls[i]);
    }
    myFile.close();
    #ifdef DEBUG_MODE
    Serial.print("wrote to file");
    #endif
  } else {
    // if the file didn't open, print an error:
    #ifdef DEBUG_MODE
    Serial.println("error opening file");
    #endif
  }
}


/* Voice edit functions */
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
      oscOneA.pulseWidth(0.25);
      oscOneB.pulseWidth(0.25);
      oscOneC.pulseWidth(0.25);
      oscOneD.pulseWidth(0.25);
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
      oscTwoA.pulseWidth(0.25);
      oscTwoB.pulseWidth(0.25);
      oscTwoC.pulseWidth(0.25);
      oscTwoD.pulseWidth(0.25);
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
      oscThreeA.pulseWidth(0.25); // TODO PWM
      oscThreeB.pulseWidth(0.25);
      oscThreeC.pulseWidth(0.25);
      oscThreeD.pulseWidth(0.25);
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

void setLfoShape(uint8_t wave) {
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

void clearEverything() {
  menuCount = 0;
  presetNumber = -1;
  for (int i = 0; i < NUM_CONTROLS; i++) {
    paramLocks[i] = false;
  }
  for (int z = 0; z < NUM_VOICES; z++) {
    voices[z] = 0;
  }
}

void updateEncoder() {
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
  float valueNorm = value * DIV127;
  switch (number) {
    case 11 ... 14: { // OSC1...3 amp
      float gain = valueNorm*0.5;
      voiceMixerA.gain(number-11, gain);
      voiceMixerB.gain(number-11, gain);
      voiceMixerC.gain(number-11, gain);
      voiceMixerD.gain(number-11, gain);
      break;
    }

    case 15:
      setOsc1Shape(value);
      break;

    case 16:
      setOsc2Shape(value);
      break;

    case 17:
      setOsc3Shape(value);
    break;

    case 18:
      setLfoShape(value);
    break;

      lfo1Freq = sq(valueNorm)*20; // lfo1 freq

      lfo1Amt = valueNorm/256; // lfo1 amount

      lfo2Freq = sq(valueNorm)*20; // lfo2 freq

      lfo2Amt = valueNorm/256; // lfo2 amount

      masterDetune = sq(valueNorm); // Detune
      plusDetune =  1 + masterDetune * 0.5;
      minusDetune = 1 - masterDetune * 0.25;

      octaveKey = valueNorm * 4; // Octave
      octaveKey = int(constrain(octaveKey, 0, 3));

      filterFreq = 40 + sq(valueNorm) * 16000; // Filter cutoff freq

      filterRes = 0.7 + valueNorm * 4.3; // Filter resonance

      attackTime = sq(valueNorm) * 10000 +1;

      releaseTime = sq(valueNorm) * 10000 + 1;

      filterEnvAttackTime = sq(valueNorm) * 10000 + 1;

      filterEnvReleaseTime = sq(valueNorm) * 10000 + 1;

      delay1.delay(0, sq(valueNorm) * 999 + 1); // Delay time

      delayFbMixer.gain(1, valueNorm * 0.862); // Delay feedback

      delayFilter1.setLowpass(1, 80 + sq(valueNorm) * 10000, 1.0); // TODO setBandpass etc.

      delayMixer.gain(1, valueNorm); // Delay mix

      freeverbs1.roomsize(valueNorm); // Reverb size

      freeverbs1.damping(valueNorm); // Reverb damping

      reverbMixerL.gain(1, valueNorm); // Reverb mix
      reverbMixerR.gain(1, valueNorm);
  }
}
