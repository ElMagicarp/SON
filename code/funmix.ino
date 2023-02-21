#include <Audio.h>
#include "FunMix.h"

FunMix myDsp;
AudioInputI2S in;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(in,0,myDsp,0);
AudioConnection patchCord2(myDsp,0,out,0);
AudioConnection patchCord3(myDsp,0,out,1);

void setup() {
  Serial.begin(9600);
  AudioMemory(6);
  audioShield.enable();
  audioShield.inputSelect(AUDIO_INPUT_MIC);
  audioShield.micGain(20); // in dB
  audioShield.volume(0.8);
  myDsp.setParamValue("Volume",0.5);
  myDsp.setParamValue("Low",0);
  myDsp.setParamValue("High",0);
}

void loop() {
  float vol = (float)analogRead(A0); // from 0 to 1023
  vol = vol/1023.0;
  myDsp.setParamValue("Volume",vol);
  delay(50);
}
