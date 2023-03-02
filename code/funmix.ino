#include <Audio.h>s
#include "FunMix.h"

FunMix myDsp;
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
  audioShield.volume(1);
  myDsp.setParamValue("volume",0.8);
  myDsp.setParamValue("high",0);
  myDsp.setParamValue("low",0);
  myDsp.setParamValue("shift",0);
  myDsp.setParamValue("echoDelay",0);
  myDsp.setParamValue("echoFeedback",0);
}

void loop() {
  // A0, 2, 3, 8, 17, 16, 15 , 14 are free
  float vol = (float)analogRead(A17)/1023.0; // 0-1
  float hi = ((float)analogRead(A12)*40.0/1023.0)-20;
  float lo = ((float)analogRead(A10)*40.0/1023.0)-20; 
  float mid = ((float)analogRead(A11)*40.0/1023.0)-20; 
  float sh = ((float)analogRead(A14)*26.0/1023.0) - 12.0;
  float del = (float)analogRead(A15)*800.0/1023.0; // 0-1000 ms
  float feed = (float)analogRead(A16)*0.8/1023.0;
  if(del<10){
    del=0;
    feed = 0;
  }
  myDsp.setParamValue("volume",vol);
  myDsp.setParamValue("high",hi);
  myDsp.setParamValue("low",lo);
  myDsp.setParamValue("mid",mid);
  myDsp.setParamValue("echoDelay",del);
  myDsp.setParamValue("echoFeedback",feed);
  myDsp.setParamValue("shift",sh);
  delay(10);
}
