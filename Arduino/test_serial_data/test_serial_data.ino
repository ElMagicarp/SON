#include <SoftwareSerial.h>
#include <stdio.h>
#include <string.h>

//initialisation de la com serie entre teesy et arduino
SoftwareSerial ArduinoMaster(2,3);
float *data;
char * msg = "";

void setup() {
  
  //debut des com series
  Serial.begin(9600);
  ArduinoMaster.begin(9600);

}

void loop(){
  
  //lire le buffer reception
  msg = readMasterPort(); 
  //extraire data du msg reçu
  data = extractMsgData(msg);
  //verification de la data reçu
  String verifData = String(data[0])+";"+String(data[1])+";"+String(data[2])+";"+String(data[3])+";";
  Serial.println(verifData);
  
}

char * readMasterPort(){
 char *res = "";
 
 if (ArduinoMaster.available() >0) {
   char c = ArduinoMaster.read();  //gets one byte from serial buffer
   res += c; //makes the string readString
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
