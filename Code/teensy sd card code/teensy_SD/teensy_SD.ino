#include <SdFat.h>

#define HWSERIAL Serial1
#define DEBUG 0

const size_t BUF_DIM = 32768;
const uint32_t FILE_SIZE = 256UL*BUF_DIM;

SdFatSdio sd;
File file;
char filename[12];
int starttime;
int i;

void setup() {
  HWSERIAL.begin(9600);
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  while(!sd.begin()){
    #ifdef DEBUG
      Serial.println("Waiting for sd card...");
    #endif
    delay(500);
  }
  sprintf(filename, "datalog.csv");
  HWSERIAL.print('r'); // ready
  #ifdef DEBUG
    Serial.println("Ready!");
  #endif
  i = 0;
  starttime = millis();
}

void writeSD(int t, int incomingByte){
  i = (i+1)%3;
  #ifdef DEBUG
    Serial.print("Writing ");
    Serial.print(incomingByte);
    Serial.print(" at time ");
    Serial.println(t);
  #endif
  file = sd.open(filename, FILE_WRITE);
  if(i != 0) file.printf("%u,", incomingByte);
  else file.printf("%u,%u\n", incomingByte, (t-starttime));
  file.close();
}

void loop() {
  int incomingByte;
  if(HWSERIAL.available() > 0) {
    #ifdef DEBUG
      Serial.print("UART Received: " );
      Serial.println(incomingByte, DEC);
    #endif
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
