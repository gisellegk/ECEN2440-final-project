#include "DigitalShift.h" 

void DigitalShift::init() {
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_LATCH, OUTPUT);

  digitalWriteFast(PIN_RESET,0);
  digitalWriteFast(PIN_DATA,0);
  digitalWriteFast(PIN_CLK,0);
  digitalWriteFast(PIN_LATCH,0);

  digitalWriteFast(PIN_RESET,1);  

  outState = 0;
  
}

 void DigitalShift::setOutput(int channelNumber,bool value){
  if(channelNumber < 0 || channelNumber > 11) return;
  if(value) 
  outState =outState|(1<<channelNumber);

  else
  outState = outState &~(1<<channelNumber);

  DigitalShift::shiftOut(outState); 
 }

 void DigitalShift::shiftOut(uint16_t data){
  digitalWriteFast(PIN_LATCH,0);
  for (int i=11; i>=0; i--)  {
    digitalWriteFast(PIN_CLK, 0);
    
    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( data & (1<<i) ) {
      digitalWriteFast(PIN_DATA, 1);        //sets data pin high 
    }
    else {  
      digitalWriteFast(PIN_DATA,0);        //sets data pin low 
    }

 // __asm__ volatile("nop");            // Delay for write
 // __asm__ volatile("nop");

    
    //register shifts bits on upstroke of clock pin  
    digitalWrite(PIN_CLK, 1);             
    //zero the data pin after shift to prevent bleed through
    digitalWriteFast(PIN_DATA, 0);
  }

  //stop shifting
  digitalWriteFast(PIN_CLK, 0);

  digitalWrite(PIN_LATCH, 1);
    

  digitalWrite(PIN_LATCH, 0); 
}

 
