/* Initialize static values */
polyMixer.gain(0,.25);
polyMixer.gain(1,.25);
polyMixer.gain(2,.25);
polyMixer.gain(3,.25);

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

oscOneA.frequencyModulation(6);
oscOneB.frequencyModulation(6);
oscOneC.frequencyModulation(6);
oscOneD.frequencyModulation(6);
oscTwoA.frequencyModulation(6);
oscTwoB.frequencyModulation(6);
oscTwoC.frequencyModulation(6);
oscTwoD.frequencyModulation(6);
oscThreeA.frequencyModulation(6);
oscThreeB.frequencyModulation(6);
oscThreeC.frequencyModulation(6);
oscThreeD.frequencyModulation(6);

noiseWhite.amplitude(.125);

ampEnvA.releaseNoteOn(1);
ampEnvB.releaseNoteOn(1);
ampEnvC.releaseNoteOn(1);
ampEnvD.releaseNoteOn(1);
filterEnvA.releaseNoteOn(1);
filterEnvB.releaseNoteOn(1);
filterEnvC.releaseNoteOn(1);
filterEnvD.releaseNoteOn(1);

dcOneVolt.amplitude(1);

filterA.octaveControl(6);
filterB.octaveControl(6);
filterC.octaveControl(6);
filterD.octaveControl(6);

delayFilter1.setHighpass(0, 80, 0.7);
delayMixer.gain(0, 1);
delayFbMixer.gain(0, 1);
reverbMixerL.gain(0, 1);
reverbMixerR.gain(0, 1);
reverbInputFilter.setHighpass(0, 80, 0.7); // stage(0-3), frequency, resonance

lfo1.begin(1,1,WAVEFORM_SINE);
lfo2.begin(1,1,WAVEFORM_SINE);
