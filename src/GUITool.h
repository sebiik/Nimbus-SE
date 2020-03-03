#include "defines.h"

// GUItool: begin automatically generated code
AudioControlSGTL5000     sgtl5000_1;
AudioOutputI2S           i2s1;

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

AudioSynthNoiseWhite     noiseWhite;

AudioMixer4              voiceMixerA;
AudioMixer4              voiceMixerB;
AudioMixer4              voiceMixerC;
AudioMixer4              voiceMixerD;

AudioEffectEnvelope      ampEnvA;
AudioEffectEnvelope      ampEnvB;
AudioEffectEnvelope      ampEnvC;
AudioEffectEnvelope      ampEnvD;

AudioEffectEnvelope      filterEnvA;
AudioEffectEnvelope      filterEnvB;
AudioEffectEnvelope      filterEnvC;
AudioEffectEnvelope      filterEnvD;

AudioSynthWaveform       lfo1;
AudioSynthWaveform       lfo2;

AudioSynthWaveformDc     dcOneVolt;

AudioMixer4              filterModMixerA;
AudioMixer4              filterModMixerB;
AudioMixer4              filterModMixerC;
AudioMixer4              filterModMixerD;

AudioFilterStateVariable filterA;
AudioFilterStateVariable filterB;
AudioFilterStateVariable filterC;
AudioFilterStateVariable filterD;

AudioAnalyzePeak         peakA;
AudioAnalyzePeak         peakB;
AudioAnalyzePeak         peakC;
AudioAnalyzePeak         peakD;

AudioMixer4              polyMixer;
AudioAnalyzePeak         finalPeak;

AudioEffectDelayExternal delay1;
AudioMixer4              delayMixer;
AudioMixer4              delayFbMixer;
AudioFilterBiquad        delayFilter1;

AudioEffectFreeverbStereo freeverbs1; //TODO hp/lp filter, gentle feedback loop
AudioFilterBiquad         reverbInputFilter;
AudioMixer4               reverbMixerL;
AudioMixer4               reverbMixerR;

AudioConnection          patchCord1(oscOneA, 0, voiceMixerA, 0);
AudioConnection          patchCord2(oscOneB, 0, voiceMixerB, 0);
AudioConnection          patchCord3(oscOneC, 0, voiceMixerC, 0);
AudioConnection          patchCord4(oscOneD, 0, voiceMixerD, 0);
AudioConnection          patchCord5(oscTwoA, 0, voiceMixerA, 1);
AudioConnection          patchCord6(oscTwoB, 0, voiceMixerB, 1);
AudioConnection          patchCord7(oscTwoC, 0, voiceMixerC, 1);
AudioConnection          patchCord8(oscTwoD, 0, voiceMixerD, 1);
AudioConnection          patchCord9(oscThreeA, 0, voiceMixerA, 2);
AudioConnection          patchCord10(oscThreeB, 0, voiceMixerB, 2);
AudioConnection          patchCord11(oscThreeC, 0, voiceMixerC, 2);
AudioConnection          patchCord12(oscThreeD, 0, voiceMixerD, 2);
AudioConnection          patchCord13(noiseWhite, 0, voiceMixerA, 3);
AudioConnection          patchCord14(noiseWhite, 0, voiceMixerB, 3);
AudioConnection          patchCord15(noiseWhite, 0, voiceMixerC, 3);
AudioConnection          patchCord16(noiseWhite, 0, voiceMixerD, 3);

AudioConnection          patchCord17(voiceMixerA, 0, filterA, 0);
AudioConnection          patchCord18(voiceMixerB, 0, filterB, 0);
AudioConnection          patchCord19(voiceMixerC, 0, filterC, 0);
AudioConnection          patchCord20(voiceMixerD, 0, filterD, 0);

AudioConnection          patchCord25(filterA, 0, ampEnvA, 0);
AudioConnection          patchCord26(filterB, 0, ampEnvB, 0);
AudioConnection          patchCord27(filterC, 0, ampEnvC, 0);
AudioConnection          patchCord28(filterD, 0, ampEnvD, 0);

AudioConnection          patchCord129(dcOneVolt, 0, filterEnvA, 0);
AudioConnection          patchCord130(dcOneVolt, 0, filterEnvB, 0);
AudioConnection          patchCord131(dcOneVolt, 0, filterEnvC, 0);
AudioConnection          patchCord132(dcOneVolt, 0, filterEnvD, 0);

AudioConnection          patchCord29(filterEnvA, 0, filterModMixerA, 0);
AudioConnection          patchCord30(filterEnvB, 0, filterModMixerB, 0);
AudioConnection          patchCord31(filterEnvC, 0, filterModMixerC, 0);
AudioConnection          patchCord32(filterEnvD, 0, filterModMixerD, 0);
AudioConnection          patchCord33(lfo2, 0, filterModMixerA, 1);
AudioConnection          patchCord34(lfo2, 0, filterModMixerB, 1);
AudioConnection          patchCord35(lfo2, 0, filterModMixerC, 1);
AudioConnection          patchCord36(lfo2, 0, filterModMixerD, 1);
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
AudioConnection          patchCord49(polyMixer, finalPeak);

AudioConnection          patchCord50(polyMixer, 0, delayFbMixer, 0);
AudioConnection          patchCord51(delayFbMixer, 0, delayFilter1, 0);
AudioConnection          patchCord52(delayFilter1, 0, delay1, 0);
AudioConnection          patchCord53(delay1, 0, delayFbMixer, 1);

AudioConnection          patchCord54(polyMixer, 0, delayMixer, 0);
AudioConnection          patchCord55(delay1, 0, delayMixer, 1);

AudioConnection          patchCord56(delayMixer, 0, reverbInputFilter, 0);
AudioConnection          patchCord57(reverbInputFilter, 0, freeverbs1, 0);
AudioConnection          patchCord58(delayMixer, 0, reverbMixerL, 0);
AudioConnection          patchCord59(delayMixer, 0, reverbMixerR, 0);

AudioConnection          patchCord60(freeverbs1, 0, reverbMixerL, 1);
AudioConnection          patchCord61(freeverbs1, 1, reverbMixerR, 1);
AudioConnection          patchCord62(reverbMixerL, 0, i2s1, 0);
AudioConnection          patchCord63(reverbMixerR, 0, i2s1, 1);
// GUItool: end automatically generated code
