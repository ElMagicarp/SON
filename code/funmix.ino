#include <Audio.h>
#include "Funmix.h"

Funmix myDsp;
AudioInputI2S in;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(in,0,myDsp,0);
AudioConnection patchCord1(in,1,myDsp,1);
AudioConnection patchCord2(myDsp,1,out,1);
AudioConnection patchCord3(myDsp,0,out,0);

void setup() {
  Serial.begin(9600);
  AudioMemory(12);
  audioShield.enable();
  audioShield.inputSelect(AUDIO_INPUT_LINEIN);
  audioShield.micGain(10); // in dB
  audioShield.volume(0.8);
  myDsp.setParamValue("volume",0.8);
  myDsp.setParamValue("high",0);
  myDsp.setParamValue("low",0);
  myDsp.setParamValue("shift",0);
  myDsp.setParamValue("echoDelay",70);
  myDsp.setParamValue("echoFeedback",0.5);
}

void loop() {
  // A0, 2, 3, 8, 17, 16, 15 , 14 are free
  float vol = (float)analogRead(A17)/1023.0; // 0-1
  float hi = (float)analogRead(A12)*40.0/1023.0; // 0-40 dB
  float lo = (float)analogRead(A11)*40.0/1023.0; // 0-40 dB
  float sh = ((float)analogRead(A10)*40.0/1023.0) - 20.0; // (-20) - 20
  float del = (float)analogRead(A16)*1000.0/1023.0; // 0-1000 ms
  float feed = (float)analogRead(A13)/1023.0; // 0-1
  
  myDsp.setParamValue("volume",vol);
  myDsp.setParamValue("high",hi);
  myDsp.setParamValue("low",lo);
  myDsp.setParamValue("echoDelay",del);
  myDsp.setParamValue("echoFeedback",feed);
  myDsp.setParamValue("shift",sh);
  Serial.print(analogRead(A10));
  Serial.print(" ");
  Serial.print(analogRead(A11));
  Serial.print(" ");
  Serial.print(analogRead(A12));
  Serial.print(" ");
  Serial.print(analogRead(A13));
  Serial.print(" ");
  Serial.print(analogRead(A17));
  Serial.print(" ");
  Serial.println(analogRead(A16));
  delay(50);
}
