#ifndef DIGITALSHIFT_H_
#define DIGITALSHIFT_H_ 

#include <Arduino.h>

#define PIN_DATA 24
#define PIN_CLK 25
#define PIN_RESET 26
#define PIN_LATCH 27 

namespace DigitalShift{
  namespace {
   uint16_t outState; 
  };
  
  void init();
  void shiftOut(uint16_t data);
  void setOutput(int channelNumber,bool value);
};











#endif 
