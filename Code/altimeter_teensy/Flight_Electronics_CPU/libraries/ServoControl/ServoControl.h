/*
 * ServoControl.h
 *
 *  Created on: Jan 29, 2019
 *      Author: dnorris
 */

#ifndef SERVOCONTROL_H_
#define SERVOCONTROL_H_
#include <Arduino.h>
#include <AX12A.h>
#define SERVO_DIR_PIN 5 
#define SERVO_BAUD_RATE 1000000
#define SERVO_ID 1
#define SERVO_OPEN 512
#define SERVO_CLOSE 0
#define SERVO_SPEED 200







namespace ServoControl
{
  void init();
  int ServoPosition();
  int ServoTorqueStatus( float &Torque_Mag);
  int ServoTemp();
  int ServoVoltage();
  void ServoSetPosition(bool Servo_State);
  
 
};

#endif /* SERVOCONTROL_H_ */
