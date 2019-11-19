#include "ServoControl.h"


void setup() {
  // put your setup code here, to run once:
 ServoControl :: init();
 Serial.begin(9600);
 pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
//  if(we_want_the_engine_on){
ServoControl:: ServoSetPosition(true);    
for(int i =0; i < 50; i ++){
  bool dir;
  float mag;
  if(ServoControl::ServoTorqueStatus( mag))
    Serial.println("ERR");
  Serial.printf("mag: %f\n", mag);
  delay(100);
}
  //} else {
//ServoControl::ServoSetPosition(false);
  //}
for(int i =0; i < 50; i ++){
  bool dir;
  float mag;
  if(ServoControl::ServoTorqueStatus( mag))
    Serial.println("ERR");
  Serial.printf("mag: %f\n", mag);
  delay(100);
}
 
}
