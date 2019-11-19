#include "DigitalShift.h"

void setup() {
 DigitalShift:: init(); // put your setup code here, to run once:
 Serial.begin(9600);
}

void loop() {
   DigitalShift::setOutput(0, 1);
   Serial.println("ON");
   delay (2000);
   DigitalShift::setOutput(0, 0);
   Serial.println("OFF");
   delay (2000);
 
}
