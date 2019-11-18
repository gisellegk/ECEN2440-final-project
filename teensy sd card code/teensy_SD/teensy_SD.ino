#include <SdFat.h>


#define HWSERIAL Serial1

const size_t BUF_DIM = 32768;
const uint32_t FILE_SIZE = 256UL*BUF_DIM;

SdFatSdio sd;
File file;
char filename[12];

void setup() {
  Serial.begin(9600);
  HWSERIAL.begin(9600);
  while(!sd.begin()){
    Serial.println("Waiting for sd card...");
    delay(500);
  }
  sprintf(filename, "datalog.csv");

}

void writeSD(int t, int incomingByte){
  Serial.print("Writing ");
  Serial.print(incomingByte);
  Serial.print(" at time ");
  Serial.println(t);
  file = sd.open(filename, FILE_WRITE);
  file.printf("%u,%u\n", t, incomingByte);
  file.close();
}

void loop() {
  int incomingByte;
  if(HWSERIAL.available() > 0) {
    Serial.print("UART Received: " );
    Serial.println(incomingByte, DEC);
    incomingByte = HWSERIAL.read();
    writeSD(millis(), incomingByte);
  }
/*  int incomingByte;

  if(Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print("USB Received: " );
    Serial.println(incomingByte, DEC);
    HWSERIAL.print("USB received: ");
    HWSERIAL.println(incomingByte, DEC);
  }
  if(HWSERIAL.available() > 0) {
    incomingByte = HWSERIAL.read();
    Serial.print("UART Received: " );
    Serial.println(incomingByte, DEC);
    HWSERIAL.print("UART received: ");
    HWSERIAL.println(incomingByte, DEC);
  }*/

}
