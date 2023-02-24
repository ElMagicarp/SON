#include <Audio.h>
#include "Funmix.h"
#include <SoftwareSerial.h>
#include <stdio.h>
#include <string.h>
SoftwareSerial ArduinoMaster(0,1);
float *data;
char * msg;

Funmix myDsp;
AudioInputI2S in;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(in,0,myDsp,0);
AudioConnection patchCord1(in,0,myDsp,1);
AudioConnection patchCord2(myDsp,1,out,1);
AudioConnection patchCord3(myDsp,0,out,0);

void setup() {
  Serial.begin(9600);
  ArduinoMaster.begin(9600);
  AudioMemory(6);
  audioShield.enable();
  audioShield.inputSelect(AUDIO_INPUT_MIC);
  audioShield.micGain(10); // in dB
  audioShield.volume(0.7);
  myDsp.setParamValue("volume",0.5);
  myDsp.setParamValue("high",0);
  myDsp.setParamValue("low",0);
  myDsp.setParamValue("shift",12);
  myDsp.setParamValue("echoDelay",100);
  myDsp.setParamValue("echoFeedback",0.5);
}

void loop() {
  //float vol = (float)analogRead(A0);
  //vol = vol/1023.0;
  //myDsp.setParamValue("volume",vol);
  
  //lire le buffer reception
  msg = readMasterPort(); 
  //extraire data du msg reçu
  //data = extractMsgData(msg);
  //delay(50);
}
char * readMasterPort(){
 char *res;
 if (ArduinoMaster.available() >0) {
  for(int i =0; i<ArduinoMaster.available();i++){
    char c = ArduinoMaster.read();  //gets one byte from serial buffer
    Serial.print(c);
    res[i] = c;
    }
    Serial.println();
 }
 ArduinoMaster.flush();
 return res;
}

float * extractMsgData(char * message){
  float *res;
  int i = 0;
  
  String val = "";
  val = strtok (message,";");
  res[i] = val.toFloat();
  
  while (val != NULL)
  {
    i++;
    val = strtok (NULL, ";");
    res[i] = val.toFloat();
  }
  return res;
}
