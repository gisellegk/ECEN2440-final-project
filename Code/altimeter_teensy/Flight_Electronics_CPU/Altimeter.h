/*
 * Altimeter.h
 *
 *  Created on: Jan 28, 2019
 *      Author: erics
 */


#ifndef ALTIMETER_H_
#define ALTIMETER_H_

#include <Arduino.h>
#include <Wire.h>
#include <FastCRC.h>

#include "Config.h"

#define ALTIMITER_MODE_LOW_POWER 0x401A // up to ~300Hz ?
#define ALTIMETER_MODE_NORMAL 0x48A3 // up to 140Hz ?
#define ALTIMETER_MODE_LOW_NOISE 0x5059 // up to ~40Hz ?
#define ALTIMETER_MODE_ULTRA_LOW_NOISE 0x58E0 // up to 10Hz ?


#define p_Pa_calib_0 45000.0
#define p_Pa_calib_1 80000.0
#define p_Pa_calib_2 105000.0 
#define LUT_lower 3.5 * (1U<<20)
#define LUT_upper 11.5 * (1U<<20)
#define quadr_factor (1 / 16777216.0)
#define offst_factor 2048.0


#define CONST_M 0.0289644 // kg/mol
#define CONST_G 9.80665 // m/s2
#define CONST_R 8.3144598 // J/mol/K


// TODO: We need to determine this and actual coefficients. for good performance. for now i will leave the following as a place holder...
#define ALTITUDE_FILTER_TAP_NUM 9
static float ALTITUDE_FILTER_TAPS[ALTITUDE_FILTER_TAP_NUM] = {
	-0.034640280536991565,
	-0.06403675618096012,
	0.05175991343322914,
	0.3165201526922483,
	0.46622041259025365,
	0.3165201526922483,
	0.05175991343322914,
	-0.06403675618096012,
	-0.034640280536991565
};


// TODO: We need to determine this and actual coefficients. for good performance. for now i will leave the following as a place holder...
#define VELOCITY_FILTER_TAP_NUM 19
static float VELOCITY_FILTER_TAPS[VELOCITY_FILTER_TAP_NUM] = {
	-0.002994074332803273,
	-0.005916179653733406,
	-0.00695196690388829,
	-0.0010599565899403164,
	0.016540140887353838,
	0.047692014838514415,
	0.08896134551647339,
	0.1314913451204629,
	0.1636790063217784,
	0.17568987279905468,
	0.1636790063217784,
	0.1314913451204629,
	0.08896134551647339,
	0.047692014838514415,
	0.016540140887353838,
	-0.0010599565899403164,
	-0.00695196690388829,
	-0.005916179653733406,
	-0.002994074332803273
};

namespace Altimeter
{
	namespace
	{
		// TODO: Make this stuff ISR safe
		float altitudeFilterRingBuffer[ALTITUDE_FILTER_TAP_NUM];
		int8_t altitudeFilterRingBufferIndex=0;
		float velocityFilterRingBuffer[VELOCITY_FILTER_TAP_NUM];
		int8_t velocityFilterRingBufferIndex=0;
		uint32_t p_dout;
		uint32_t lastSampleTime=0;
		uint16_t t_dout;
		float pressure;
		float velocity;
		float temperatureC;
		uint16_t cn[4] = {0};
		FastCRC8 CRC8;
	}
	void init();
	float getVelocity();
	float getAltitude();
	float getTempK();
	float getTempC();
	float getTempF();
	uint8_t send8BitWord(uint8_t word);
	uint8_t send8BitWordWithCRC(uint8_t word, uint8_t crc);
	uint8_t send8BitWordWithCRC(uint8_t word);
	uint8_t send16BitWord(uint16_t word);
	uint8_t send16BitWordWithCRC(uint16_t word, uint8_t crc);
	uint8_t send16BitWordWithCRC(uint16_t word);
	uint8_t generateCRC8(const uint8_t *bytes, uint8_t length);
	bool updateOPT();
	bool readBytes(uint8_t* buf, uint8_t len);
	void getNewSample();
};

#endif /* ALTIMETER_H_ */
