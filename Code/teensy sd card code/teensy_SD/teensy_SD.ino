#include <SdFat.h>

#define HWSERIAL Serial1
#define DEBUG 0
#define TEENSY_LOG_LENGTH 9

const size_t BUF_DIM = 32768;
const uint32_t FILE_SIZE = 256UL*BUF_DIM;

SdFatSdio sd;
File file;
char filename[12];
int starttime;
int i;

char ack = 'n';

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
  int counter = 0;
  while(true) {
        sprintf(filename,"datalog%03d.csv",counter);

        if(sd.exists(filename)) {
            Serial.println("Iterating file counter.");
            counter+=1;
            if(counter>999){break;}
        }
        else
        {
            break;
        }
        
    }
  while(!(ack == 'a')) {
      HWSERIAL.print('r'); // ready
      Serial.println("Ready!");
      if(HWSERIAL.available() > 0) {
        Serial.print("Input available ");
        Serial.println(ack);
        ack = HWSERIAL.read();
      }
  }
  #ifdef DEBUG
    Serial.println("time to write to sd card!");
  #endif
  i = 0;
  starttime = millis();  
}

void writeSD(int t, uint8_t incomingByte){
  i = (i+1)%TEENSY_LOG_LENGTH;
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

bool pn = false;
bool ff = false;
void loop() {
  uint8_t incomingByte;
  if(HWSERIAL.available() > 0) {
    incomingByte = HWSERIAL.read();
    if(!pn){
      if( (incomingByte == 0xF1) ) {
        // trying to get rid of the first FF. 
        pn = true;
      }
      writeSD(millis(), incomingByte);
      #ifdef DEBUG
        Serial.print("UART Received: " );
        Serial.println(incomingByte, DEC);
      #endif
    } else {
      if(!ff){
        ff = true; 
        // dont log
      } else {
        writeSD(millis(), incomingByte);
        #ifdef DEBUG
          Serial.print("UART Received: " );
          Serial.println(incomingByte, DEC);
        #endif
      }
    }
    
    
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
