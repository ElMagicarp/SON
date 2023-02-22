#include <SoftwareSerial.h>

//initialisation de la com serie entre teesy et arduino
SoftwareSerial ArduinoSlave(2,3);
float *data;
String msg = "";

//initialisation des capteurs
float potar = 0;
float linear_G = 0;
float linear_M = 0;
float linear_D = 0;

void setup() {

  //debut des com series
  Serial.begin(9600);
  ArduinoSlave.begin(9600);
}

void loop() {
  
  //flush du cache msg
  msg ="";
  
  //mesure val capteurs
  potar = normalisation(analogRead(A0));
  linear_G = normalisation(analogRead(A1));
  linear_M = normalisation(analogRead(A2));
  linear_D = normalisation(analogRead(A3));

  //creation du message
  msg= msgAdd(msg,potar);
  msg= msgAdd(msg,linear_G);
  msg= msgAdd(msg,linear_M);
  msg= msgAdd(msg,linear_D);

  //check contenu msg
  Serial.println(msg);

  //com serial teensy
  ArduinoSlave.print(msg);

  delay(1000);
}

String msgAdd(String msg, float val){
  String res = "";
  res = msg + String(val)+";";
  return res;
}

float normalisation(float val){
  float res =0;
  int pourcent=0;
  pourcent =int((val/653.)*100);
  res = (pourcent%101)/100.;
  return res;
}
