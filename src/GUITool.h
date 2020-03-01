// GUItool: begin automatically generated code
AudioControlSGTL5000     sgtl5000_1;     //xy=1371.5,273
AudioOutputI2S           i2s1;           //xy=1592.5,691

AudioSynthWaveform       oscOneA;      //xy=454.5,300
AudioSynthWaveform       oscOneB;      //xy=387.5,590
AudioSynthWaveform       oscOneC;      //xy=411.5,810
AudioSynthWaveform       oscOneD;      //xy=390.5,1009

AudioSynthWaveform       oscTwoA;      //xy=454.5,336
AudioSynthWaveform       oscTwoB;      //xy=387.5,624
AudioSynthWaveform       oscTwoC;      //xy=410.5,845
AudioSynthWaveform       oscTwoD;      //xy=389.5,1045

AudioSynthWaveform       oscThreeA;    //xy=458.5,373
AudioSynthWaveform       oscThreeB;    //xy=392.5,660
AudioSynthWaveform       oscThreeC;    //xy=414.5,881
AudioSynthWaveform       oscThreeD;    //xy=392.5,1080

AudioSynthNoiseWhite     noiseWhite;    //xy=455.5,411
// AudioSynthNoiseWhite     noiseVoiceA;    //xy=455.5,411
// AudioSynthNoiseWhite     noiseVoiceB;    //xy=393.5,694
// AudioSynthNoiseWhite     noiseVoiceC;    //xy=411.5,917
// AudioSynthNoiseWhite     noiseVoiceD;    //xy=392.5,1114

AudioMixer4              voiceMixerA;    //xy=635.5,364
AudioMixer4              voiceMixerB;    //xy=567.5,655
AudioMixer4              voiceMixerC;    //xy=578.5,877
AudioMixer4              voiceMixerD;    //xy=579.5,1070

AudioSynthWaveformDc     ampEnvA;      //xy=639.5,306
AudioSynthWaveformDc     ampEnvB;      //xy=577.5,600
AudioSynthWaveformDc     ampEnvC;      //xy=578.5,817
AudioSynthWaveformDc     ampEnvD;      //xy=588.5,1006

AudioEffectMultiply      multiplyA;      //xy=796.5,354
AudioEffectMultiply      multiplyB;      //xy=726.5,627
AudioEffectMultiply      multiplyC;      //xy=738.5,848
AudioEffectMultiply      multiplyD;      //xy=738.5,1035

AudioSynthWaveform       LFO1;           //xy=757.5,770

AudioSynthWaveformSine   LFO2;           //xy=1050.5,232
AudioSynthWaveformDc     lfo2Amt;        //xy=1050.5,185

AudioMixer4              lfoMixer;       //xy=1207.5,235
AudioAnalyzePeak         lfoPeak;        //xy=1364.5,229

AudioSynthWaveformDc     filterEnvA;     //xy=854.5,445
AudioSynthWaveformDc     filterEnvB;     //xy=849.5,675
AudioSynthWaveformDc     filterEnvC;     //xy=860.5,892
AudioSynthWaveformDc     filterEnvD;     //xy=819.5,1113

AudioMixer4              filterModMixerA; //xy=1007.5,475
AudioMixer4              filterModMixerB; //xy=1002.5,727
AudioMixer4              filterModMixerC; //xy=1012.5,950
AudioMixer4              filterModMixerD; //xy=977.5,1176

AudioFilterStateVariable filterA;        //xy=1172.5,434
AudioFilterStateVariable filterB;        //xy=1183.5,673
AudioFilterStateVariable filterC;        //xy=1183.5,865
AudioFilterStateVariable filterD;        //xy=1175.5,1097

AudioAnalyzePeak         peakA;          //xy=1187.5,365
AudioAnalyzePeak         peakB;          //xy=1205.5,557
AudioAnalyzePeak         peakC;          //xy=1183.5,775
AudioAnalyzePeak         peakD;          //xy=1183.5,1011

AudioMixer4              finalMixer;     //xy=1388.5,692
AudioAnalyzePeak         finalPeak;      //xy=1586.5,779

AudioEffectDelayExternal delay1;
AudioMixer4              delayMixer;     //xy=1388.5,692
AudioMixer4              delayFbMixer;     //xy=1388.5,692
AudioFilterBiquad        delayFilter1;        //xy=1172.5,434

AudioEffectFreeverbStereo freeverbs1; //TODO hp/lp filter, gentle feedback loop
AudioFilterBiquad         reverbInputFilter;        //xy=1172.5,434
AudioMixer4               reverbMixerL;     //xy=1388.5,692
AudioMixer4               reverbMixerR;     //xy=1388.5,692

AudioConnection          patchCord1(oscOneB, 0, voiceMixerB, 0);
AudioConnection          patchCord2(oscTwoB, 0, voiceMixerB, 1);
AudioConnection          patchCord3(oscTwoD, 0, voiceMixerD, 1);
AudioConnection          patchCord4(oscOneD, 0, voiceMixerD, 0);
AudioConnection          patchCord5(oscThreeB, 0, voiceMixerB, 2);
AudioConnection          patchCord6(noiseWhite, 0, voiceMixerB, 3);
AudioConnection          patchCord7(oscThreeD, 0, voiceMixerD, 2);
AudioConnection          patchCord8(noiseWhite, 0, voiceMixerD, 3);
AudioConnection          patchCord9(oscTwoC, 0, voiceMixerC, 1);
AudioConnection          patchCord10(oscOneC, 0, voiceMixerC, 0);
AudioConnection          patchCord11(noiseWhite, 0, voiceMixerC, 3);
AudioConnection          patchCord12(oscThreeC, 0, voiceMixerC, 2);
AudioConnection          patchCord13(oscOneA, 0, voiceMixerA, 0);
AudioConnection          patchCord14(oscTwoA, 0, voiceMixerA, 1);
AudioConnection          patchCord15(noiseWhite, 0, voiceMixerA, 3);
AudioConnection          patchCord16(oscThreeA, 0, voiceMixerA, 2);
AudioConnection          patchCord17(voiceMixerB, 0, multiplyB, 1);
AudioConnection          patchCord18(ampEnvB, 0, multiplyB, 0);
AudioConnection          patchCord19(ampEnvC, 0, multiplyC, 0);
AudioConnection          patchCord20(voiceMixerC, 0, multiplyC, 1);
AudioConnection          patchCord21(voiceMixerD, 0, multiplyD, 1);
AudioConnection          patchCord22(ampEnvD, 0, multiplyD, 0);
AudioConnection          patchCord23(voiceMixerA, 0, multiplyA, 1);
AudioConnection          patchCord24(ampEnvA, 0, multiplyA, 0);
AudioConnection          patchCord25(multiplyB, 0, filterB, 0);
AudioConnection          patchCord26(multiplyC, 0, filterC, 0);
AudioConnection          patchCord27(multiplyD, 0, filterD, 0);
AudioConnection          patchCord28(LFO1, 0, filterModMixerA, 1);
AudioConnection          patchCord29(LFO1, 0, filterModMixerB, 1);
AudioConnection          patchCord30(LFO1, 0, filterModMixerC, 1);
AudioConnection          patchCord31(LFO1, 0, filterModMixerD, 1);
AudioConnection          patchCord32(multiplyA, 0, filterA, 0);
AudioConnection          patchCord33(filterEnvD, 0, filterModMixerD, 0);
AudioConnection          patchCord34(filterEnvB, 0, filterModMixerB, 0);
AudioConnection          patchCord35(filterEnvA, 0, filterModMixerA, 0);
AudioConnection          patchCord36(filterEnvC, 0, filterModMixerC, 0);
AudioConnection          patchCord37(filterModMixerD, 0, filterD, 1);
AudioConnection          patchCord38(filterModMixerB, 0, filterB, 1);
AudioConnection          patchCord39(filterModMixerA, 0, filterA, 1);
AudioConnection          patchCord40(filterModMixerC, 0, filterC, 1);
AudioConnection          patchCord41(lfo2Amt, 0, lfoMixer, 0);
AudioConnection          patchCord42(LFO2, 0, lfoMixer, 1);
AudioConnection          patchCord43(filterA, 0, finalMixer, 0);
AudioConnection          patchCord44(filterA, 0, peakA, 0);
AudioConnection          patchCord45(filterD, 0, finalMixer, 3);
AudioConnection          patchCord46(filterD, 0, peakD, 0);
AudioConnection          patchCord47(filterB, 0, finalMixer, 1);
AudioConnection          patchCord48(filterB, 0, peakB, 0);
AudioConnection          patchCord49(filterC, 0, finalMixer, 2);
AudioConnection          patchCord50(filterC, 0, peakC, 0);
AudioConnection          patchCord51(lfoMixer, lfoPeak);
AudioConnection          patchCord52(finalMixer, finalPeak);

AudioConnection          patchCord53(finalMixer, 0, delayFbMixer, 0);
AudioConnection          patchCord54(delayFbMixer, 0, delayFilter1, 0);
AudioConnection          patchCord55(delayFilter1, 0, delay1, 0);
AudioConnection          patchCord56(delay1, 0, delayFbMixer, 1);

AudioConnection          patchCord57(finalMixer, 0, delayMixer, 0);
AudioConnection          patchCord58(delay1, 0, delayMixer, 1);

AudioConnection          patchCord59(delayMixer, 0, reverbInputFilter, 0);
AudioConnection          patchCord60(reverbInputFilter, 0, freeverbs1, 0);
AudioConnection          patchCord61(delayMixer, 0, reverbMixerL, 0);
AudioConnection          patchCord62(delayMixer, 0, reverbMixerR, 0);

AudioConnection          patchCord63(freeverbs1, 0, reverbMixerL, 1);
AudioConnection          patchCord64(freeverbs1, 1, reverbMixerR, 1);
AudioConnection          patchCord65(reverbMixerL, 0, i2s1, 0);
AudioConnection          patchCord66(reverbMixerR, 0, i2s1, 1);
// GUItool: end automatically generated code
