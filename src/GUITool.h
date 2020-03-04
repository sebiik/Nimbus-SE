#include "defines.h"

/* Input, output */
AudioControlSGTL5000     sgtl5000_1;
AudioOutputI2S           i2sOutput;
AudioInputI2S            i2sInput;

/* Oscillators, noise generator */
AudioSynthWaveformModulated       oscOneA;
AudioSynthWaveformModulated       oscOneB;
AudioSynthWaveformModulated       oscOneC;
AudioSynthWaveformModulated       oscOneD;
AudioSynthWaveformModulated       oscTwoA;
AudioSynthWaveformModulated       oscTwoB;
AudioSynthWaveformModulated       oscTwoC;
AudioSynthWaveformModulated       oscTwoD;
AudioSynthWaveformModulated       oscThreeA;
AudioSynthWaveformModulated       oscThreeB;
AudioSynthWaveformModulated       oscThreeC;
AudioSynthWaveformModulated       oscThreeD;
AudioSynthNoiseWhite              noiseWhite;

/* Audio, modulation mixers */
AudioMixer4              voiceMixerA;
AudioMixer4              voiceMixerB;
AudioMixer4              voiceMixerC;
AudioMixer4              voiceMixerD;
AudioMixer4              polyMixer;
AudioMixer4              pitchModMixerA;
AudioMixer4              pitchModMixerB;
AudioMixer4              pitchModMixerC;
AudioMixer4              pitchModMixerD;
AudioMixer4              filterModMixerA;
AudioMixer4              filterModMixerB;
AudioMixer4              filterModMixerC;
AudioMixer4              filterModMixerD;

/* Amp, filter, pitch envelopes, 1V reference */
AudioEffectEnvelope      ampEnvA;
AudioEffectEnvelope      ampEnvB;
AudioEffectEnvelope      ampEnvC;
AudioEffectEnvelope      ampEnvD;
AudioEffectEnvelope      filterEnvA;
AudioEffectEnvelope      filterEnvB;
AudioEffectEnvelope      filterEnvC;
AudioEffectEnvelope      filterEnvD;
AudioEffectEnvelope      pitchEnvA; // TODO make aux envelope
AudioEffectEnvelope      pitchEnvB;
AudioEffectEnvelope      pitchEnvC;
AudioEffectEnvelope      pitchEnvD;
AudioSynthWaveformDc     dcOneVolt;

/* LFOs */
AudioSynthWaveform       lfo1;
AudioSynthWaveform       lfo2;

/* Filters */
AudioFilterStateVariable filterA;
AudioFilterStateVariable filterB;
AudioFilterStateVariable filterC;
AudioFilterStateVariable filterD;

/* Peak analyzers */
AudioAnalyzePeak         peakA;
AudioAnalyzePeak         peakB;
AudioAnalyzePeak         peakC;
AudioAnalyzePeak         peakD;
AudioAnalyzePeak         finalPeak;

/* Delay effect */
AudioEffectDelayExternal delay1;
AudioMixer4              delayMixer;
AudioMixer4              delayFbMixer;
AudioFilterStateVariable delayFilter; // TODO state variable

/* Reverb effect */
AudioEffectFreeverbStereo freeverbs; //TODO gentle feedback loop
AudioFilterStateVariable  reverbInputFilter; // TODO state variable
AudioMixer4               reverbMixerL;
AudioMixer4               reverbMixerR;

/* Osc connections */
AudioConnection          patchCord0(oscOneA,     0, voiceMixerA, 0);
AudioConnection          patchCord1(oscOneB,     0, voiceMixerB, 0);
AudioConnection          patchCord2(oscOneC,     0, voiceMixerC, 0);
AudioConnection          patchCord3(oscOneD,     0, voiceMixerD, 0);
AudioConnection          patchCord4(oscTwoA,     0, voiceMixerA, 1);
AudioConnection          patchCord5(oscTwoB,     0, voiceMixerB, 1);
AudioConnection          patchCord6(oscTwoC,     0, voiceMixerC, 1);
AudioConnection          patchCord7(oscTwoD,     0, voiceMixerD, 1);
AudioConnection          patchCord8(oscThreeA,   0, voiceMixerA, 2);
AudioConnection          patchCord9(oscThreeB,   0, voiceMixerB, 2);
AudioConnection          patchCord10(oscThreeC,  0, voiceMixerC, 2);
AudioConnection          patchCord11(oscThreeD,  0, voiceMixerD, 2);
AudioConnection          patchCord12(noiseWhite, 0, voiceMixerA, 3);
AudioConnection          patchCord13(noiseWhite, 0, voiceMixerB, 3);
AudioConnection          patchCord14(noiseWhite, 0, voiceMixerC, 3);
AudioConnection          patchCord15(noiseWhite, 0, voiceMixerD, 3);

AudioConnection          patchCord133(pitchEnvA, 0, pitchModMixerA, 0);
AudioConnection          patchCord134(pitchEnvB, 0, pitchModMixerB, 0);
AudioConnection          patchCord135(pitchEnvC, 0, pitchModMixerC, 0);
AudioConnection          patchCord136(pitchEnvD, 0, pitchModMixerD, 0);
AudioConnection          patchCord163(lfo1,      0, pitchModMixerA, 1);
AudioConnection          patchCord164(lfo1,      0, pitchModMixerB, 1);
AudioConnection          patchCord165(lfo1,      0, pitchModMixerC, 1);
AudioConnection          patchCord166(lfo1,      0, pitchModMixerD, 1);

AudioConnection          patchCord101(pitchModMixerA, 0, oscOneA, 0);
AudioConnection          patchCord102(pitchModMixerB, 0, oscOneB, 0);
AudioConnection          patchCord103(pitchModMixerC, 0, oscOneC, 0);
AudioConnection          patchCord104(pitchModMixerD, 0, oscOneD, 0);
AudioConnection          patchCord105(pitchModMixerA, 0, oscTwoA, 0);
AudioConnection          patchCord106(pitchModMixerB, 0, oscTwoB, 0);
AudioConnection          patchCord107(pitchModMixerC, 0, oscTwoC, 0);
AudioConnection          patchCord108(pitchModMixerD, 0, oscTwoD, 0);
AudioConnection          patchCord109(pitchModMixerA, 0, oscThreeA, 0);
AudioConnection          patchCord110(pitchModMixerB, 0, oscThreeB, 0);
AudioConnection          patchCord111(pitchModMixerC, 0, oscThreeC, 0);
AudioConnection          patchCord112(pitchModMixerD, 0, oscThreeD, 0);

AudioConnection          patchCord17(voiceMixerA, 0, filterA, 0);
AudioConnection          patchCord18(voiceMixerB, 0, filterB, 0);
AudioConnection          patchCord19(voiceMixerC, 0, filterC, 0);
AudioConnection          patchCord20(voiceMixerD, 0, filterD, 0);

AudioConnection          patchCord25(filterA, 0, ampEnvA, 0);
AudioConnection          patchCord26(filterB, 0, ampEnvB, 0);
AudioConnection          patchCord27(filterC, 0, ampEnvC, 0);
AudioConnection          patchCord28(filterD, 0, ampEnvD, 0);

AudioConnection          patchCord139(dcOneVolt, 0, filterEnvA, 0);
AudioConnection          patchCord140(dcOneVolt, 0, filterEnvB, 0);
AudioConnection          patchCord141(dcOneVolt, 0, filterEnvC, 0);
AudioConnection          patchCord142(dcOneVolt, 0, filterEnvD, 0);
AudioConnection          patchCord169(dcOneVolt, 0, pitchEnvA, 0);
AudioConnection          patchCord170(dcOneVolt, 0, pitchEnvB, 0);
AudioConnection          patchCord171(dcOneVolt, 0, pitchEnvC, 0);
AudioConnection          patchCord172(dcOneVolt, 0, pitchEnvD, 0);

AudioConnection          patchCord29(filterEnvA, 0, filterModMixerA, 0);
AudioConnection          patchCord30(filterEnvB, 0, filterModMixerB, 0);
AudioConnection          patchCord31(filterEnvC, 0, filterModMixerC, 0);
AudioConnection          patchCord32(filterEnvD, 0, filterModMixerD, 0);
AudioConnection          patchCord33(lfo2,       0, filterModMixerA, 1);
AudioConnection          patchCord34(lfo2,       0, filterModMixerB, 1);
AudioConnection          patchCord35(lfo2,       0, filterModMixerC, 1);
AudioConnection          patchCord36(lfo2,       0, filterModMixerD, 1);
AudioConnection          patchCord37(filterModMixerA, 0, filterA, 1);
AudioConnection          patchCord38(filterModMixerB, 0, filterB, 1);
AudioConnection          patchCord39(filterModMixerC, 0, filterC, 1);
AudioConnection          patchCord40(filterModMixerD, 0, filterD, 1);

AudioConnection          patchCord41(ampEnvA, 0, polyMixer, 0);
AudioConnection          patchCord42(ampEnvB, 0, polyMixer, 1);
AudioConnection          patchCord43(ampEnvC, 0, polyMixer, 2);
AudioConnection          patchCord44(ampEnvD, 0, polyMixer, 3);

AudioConnection          patchCord45(ampEnvA, 0, peakA, 0);
AudioConnection          patchCord46(ampEnvB, 0, peakB, 0);
AudioConnection          patchCord47(ampEnvC, 0, peakC, 0);
AudioConnection          patchCord48(ampEnvD, 0, peakD, 0);
AudioConnection          patchCord49(polyMixer, 0, finalPeak, 0);

AudioConnection          patchCord50(polyMixer,    0, delayFbMixer, 0);
AudioConnection          patchCord51(delayFbMixer, 0, delayFilter, 0);
AudioConnection          patchCord52(delayFilter,  OUTPUT_LOWPASS, delay1, 0);
AudioConnection          patchCord53(delay1,       0, delayFbMixer, 1);

AudioConnection          patchCord54(polyMixer, 0, delayMixer, 0);
AudioConnection          patchCord55(delay1, 0, delayMixer, 1);

AudioConnection          patchCord56(delayMixer, 0, reverbInputFilter, 0);
AudioConnection          patchCord57(reverbInputFilter, OUTPUT_HIGHPASS, freeverbs, 0);
AudioConnection          patchCord58(delayMixer, 0, reverbMixerL, 0);
AudioConnection          patchCord59(delayMixer, 0, reverbMixerR, 0);

AudioConnection          patchCord60(freeverbs,   0, reverbMixerL, 1);
AudioConnection          patchCord61(freeverbs,   1, reverbMixerR, 1);
AudioConnection          patchCord62(reverbMixerL, 0, i2sOutput, 0);
AudioConnection          patchCord63(reverbMixerR, 0, i2sOutput, 1);
// GUItool: end automatically generated code
