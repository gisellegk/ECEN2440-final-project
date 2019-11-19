/*
 * ServoControl.cpp
 *
 *  Created on: Jan 29, 2019
 *      Author: dnorris
 */

#include "ServoControl.h"

void ServoControl::init()
{
  ax12a.begin(SERVO_BAUD_RATE, SERVO_DIR_PIN, &Serial2 );
  
}
int ServoControl::ServoPosition()
{
  int Servo_Position = ax12a.readPosition(SERVO_ID);
  return Servo_Position;
}
int ServoControl::ServoTorqueStatus(float &Torque_Mag)
{
  int Servo_Torque = ax12a.readLoad(SERVO_ID);
  if(Servo_Torque == -1 || Servo_Torque & (1<<15) != 0) return -1;
  bool Torque_Dir = (Servo_Torque & 1<<10)!=0;
  Torque_Mag = (Servo_Torque & 0x3FF)/1024.0 ;
  if (Torque_Dir)
  Torque_Mag = -Torque_Mag;
  return 0;
}
int ServoControl::ServoTemp()
{
  int Servo_Temp = ax12a.readTemperature(SERVO_ID);
  return Servo_Temp;
}
int ServoControl::ServoVoltage()
{
  int Servo_Voltage = ax12a.readVoltage(SERVO_ID);
  return Servo_Voltage;
}
void ServoControl::ServoSetPosition(bool Servo_State){
  if(Servo_State) {
    ax12a.moveSpeed(SERVO_ID, SERVO_OPEN,SERVO_SPEED);
  } else {
    ax12a.moveSpeed(SERVO_ID, SERVO_CLOSE,SERVO_SPEED);
  }
}

