/*
 * Altimeter.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: erics
 */

#include "Altimeter.h"

void Altimeter::init()
{
	Wire.setSCL(I2C_PIN_SCL);
	Wire.setSDA(I2C_PIN_SDA);
	Wire.setClock(I2C_CLOCK_SPEED);
	Wire.setTimeout(I2C_TIMEOUT);
	Wire.begin();

	velocity = 0;
	pressure = 0;

	send16BitWord(0xEFC8); // ask for part number
	uint8_t buf[2] = {0};
	readBytes(buf, 2);
	if((buf[1]&0b1000))
	{
		uint8_t partNumber = buf[1] & 0b11111; // we don't need the msb... ((buf[0] << 8) | buf[1]) & 0b11111;

		char buffer[5];
		itoa(partNumber & 0b11111, buffer, 2);
		DEBUGSERIAL.printf("Altimeter detected: ICP-%s\n", buffer);
	}
	else
	{
		DEBUGSERIAL.printf("Altimeter NOT detected!\n");
		return;
	}

	send16BitWord(0x805D); // soft reset
	delay(1);
	if(!updateOPT()) DEBUGSERIAL.printf("Unable to get Altimeter OPT params!\n");
	send16BitWord(0x805D); // soft reset
	delay(1);
	send16BitWord(ALTIMITER_MODE_LOW_POWER);
}

bool Altimeter::updateOPT()
{
	// get OPT calibration parameters

	send16BitWord(0xC595); // move register pointer
	send16BitWordWithCRC(0x0066, 0x9C); // set up OPT Read
	for(int i=0; i<4; i++)
	{
		send16BitWord(0xC7F7); // increment OPT register pointer
		uint8_t cnbuf[2] = {0};
		if(readBytes(cnbuf, 2))
			cn[i] = (cnbuf[0] << 8) | cnbuf[1];
		else
			return false;
		DEBUGSERIAL.printf("cn[%i] = 0x%X\n", i, cn[i]);
	}
	return true;
}

float Altimeter::getAltitude()
{
	float altitudeResult = 0;
	for(int i=0; i<ALTITUDE_FILTER_TAP_NUM; i++)
	{
		uint8_t ringIndex=(i+altitudeFilterRingBufferIndex)%ALTITUDE_FILTER_TAP_NUM;
		altitudeResult+=ALTITUDE_FILTER_TAPS[i]*altitudeFilterRingBuffer[ringIndex];
	}
	return altitudeResult;
}

float Altimeter::getVelocity()
{
	float velocityResult = 0;
	for(int i=0; i<VELOCITY_FILTER_TAP_NUM; i++)
	{
		uint8_t ringIndex=(i+velocityFilterRingBufferIndex)%VELOCITY_FILTER_TAP_NUM;
		velocityResult+=VELOCITY_FILTER_TAPS[i]*velocityFilterRingBuffer[ringIndex];
	}
	return velocityResult;
}

void Altimeter::getNewSample()
{
	uint8_t buf[6] = {0};

	bool sampleIsReady = false;
	for(int i=0; i<10 && !sampleIsReady; i++){
		delayMicroseconds(1);
		uint8_t len = Wire.requestFrom((unsigned char)ALTIMETER_ADDRESS, 9u);
		//DEBUGSERIAL.printf("len: %u\n", len);
		if(len > 0) sampleIsReady = true;
	}
	if(!sampleIsReady)
	{
		DEBUGSERIAL.printf("Altimeter Sample Timeout!\n");
		return;
	}
	for(int i=0; i<3; i++)
	{
		buf[0+i*2] = Wire.read();
		buf[1+i*2] = Wire.read();
		//DEBUGSERIAL.printf("new samp byte %i: 0x%02X, byte %i: 0x%2X",i*2,buf[0+i*2],1+i*2,buf[1+i*2]);
		uint8_t newcrc = Wire.read();
		uint8_t expcrc = generateCRC8(buf+i*2, 2);
		if(expcrc != newcrc)
		{
			DEBUGSERIAL.printf("Altimeter CRC ERROR! ExpectedCRC: 0x%X, ReceivedCRC: 0x%X", expcrc, newcrc);
		}
	}

	uint8_t P_MMSB = buf[0];
	uint8_t P_MLSB = buf[1];
	uint8_t P_LMSB = buf[2];
	// uint8_t P_LLSB = buf[3]; we dont use this byte..., cause we dont need it!
	uint8_t T_MSB = buf[4];
	uint8_t T_LSB = buf[5];
	p_dout = P_MMSB << 16 | P_MLSB << 8 | P_LMSB;
	t_dout = T_MSB << 8 | T_LSB;

	float t = (float)(t_dout - 32768.0);
	float s0 = LUT_lower + (float)(cn[0] * t * t) * quadr_factor;
	float s1 = offst_factor * cn[3] + (float)(cn[1] * t * t) * quadr_factor;
	float s2 = LUT_upper + (float)(cn[2] * t * t) * quadr_factor;
	float A, B, C;
    C = (s0 * s1 * (p_Pa_calib_0 - p_Pa_calib_1) +
         s1 * s2 * (p_Pa_calib_1 - p_Pa_calib_2) +
         s2 * s0 * (p_Pa_calib_2 - p_Pa_calib_0)) /
        (s2 * (p_Pa_calib_0 - p_Pa_calib_1) +
         s0 * (p_Pa_calib_1 - p_Pa_calib_2) +
         s1 * (p_Pa_calib_2 - p_Pa_calib_0));
    A = (p_Pa_calib_0 * s0 - p_Pa_calib_1 * s1 - (p_Pa_calib_1 - p_Pa_calib_0) * C) / (s0 - s1);
    B = (p_Pa_calib_0 - A) * (s0 + C);

	pressure = A + B/(C+p_dout);
	temperatureC = -45 + 175.0/(float)(1<<16) * t_dout;


	// Note, this function is the inverse of the Barometric Formula
	// See https://en.wikipedia.org/wiki/Barometric_formula for definition
	// also see scripts/altitudecalc.m for a MATLAB script to test this function
	float newAlt;
	if (pressure > 22632.0)
	{
		const float L=-0.0065;
		const float Tb=288.15;
		const float Ps=101325.00;
		newAlt = Tb/(L*expf( logf(pressure/Ps) / ((CONST_G*CONST_M)/(CONST_R*L))))-Tb/L;
	}
	else if(pressure > 5474.90)
	{
		const float H=11000;
		const float Tb=216.65;
		const float Ps=22632.10;
		newAlt = -Tb*CONST_R*logf(pressure/Ps)/(CONST_G*CONST_M)+H;
	}
	else
	{
		const float  H=20000;
		const float L=0.001;
		const float Tb=216.65;
		const float Ps=5474.89;
		newAlt = Tb/(L*expf( logf(pressure/Ps) / ((CONST_G*CONST_M)/(CONST_R*L))))-Tb/L+H;
	}
	//printf("alt %.3f, %.3f\n", pressure, newAlt);
	DEBUGSERIAL.printf("pressure: %f, altitude: %f\n", pressure, newAlt);
	float lastAltitude = altitudeFilterRingBuffer[altitudeFilterRingBufferIndex];
	uint32_t newTime = micros();
	uint32_t diff = newTime-lastSampleTime;
	if(diff!=0)
	{
		velocityFilterRingBufferIndex++;
		if(velocityFilterRingBufferIndex>=VELOCITY_FILTER_TAP_NUM) velocityFilterRingBufferIndex = 0;
		velocityFilterRingBuffer[velocityFilterRingBufferIndex] = (newAlt-lastAltitude)/(float)(diff);
	}
	altitudeFilterRingBufferIndex++;
	if(altitudeFilterRingBufferIndex>=ALTITUDE_FILTER_TAP_NUM) altitudeFilterRingBufferIndex = 0;
	altitudeFilterRingBuffer[altitudeFilterRingBufferIndex] = newAlt;

	send16BitWord(ALTIMITER_MODE_LOW_POWER);
}

float Altimeter::getTempC()
{
	return temperatureC;
}

float Altimeter::getTempK()
{
	return temperatureC - 273.15;
}

float Altimeter::getTempF()
{
	return 1.8*temperatureC + 32;
}

uint8_t Altimeter::send8BitWord(uint8_t word)
{
	Wire.beginTransmission(ALTIMETER_ADDRESS);
	Wire.send(word & 0xFF);
	uint8_t err = Wire.endTransmission();
	if(err) DEBUGSERIAL.printf("Altimeter i2c err: %x, I sent: 0x%x\n", err, word);
	return err;
}

uint8_t Altimeter::send8BitWordWithCRC(uint8_t word, uint8_t crc)
{
	Wire.beginTransmission(ALTIMETER_ADDRESS);
	Wire.send(word & 0xFF);
	Wire.send(crc);
	uint8_t err = Wire.endTransmission();
	if(err) DEBUGSERIAL.printf("Altimeter i2c err: %x, I sent: 0x%x\n", err, word);
	return err;
}


uint8_t Altimeter::send8BitWordWithCRC(uint8_t word)
{
	uint8_t wordbytes[1] = { word & 0xFF };
	uint8_t crc = generateCRC8(wordbytes, 1);
	return send8BitWordWithCRC(word, crc);
}

uint8_t Altimeter::send16BitWord(uint16_t word)
{
	Wire.beginTransmission(ALTIMETER_ADDRESS);
	Wire.send((word >> 8) & 0xFF);
	Wire.send(word & 0xFF);
	uint8_t err = Wire.endTransmission();
	if(err) DEBUGSERIAL.printf("Altimeter i2c err: %x, I sent: 0x%x\n", err, word);
	return err;
}

uint8_t Altimeter::send16BitWordWithCRC(uint16_t word, uint8_t crc)
{
	Wire.beginTransmission(ALTIMETER_ADDRESS);
	Wire.send((word >> 8) & 0xFF);
	Wire.send(word & 0xFF);
	Wire.send(crc);
	uint8_t err = Wire.endTransmission();
	if(err) DEBUGSERIAL.printf("Altimeter i2c err: %x, I sent: 0x%x\n", err, word);
	return err;
}


uint8_t Altimeter::send16BitWordWithCRC(uint16_t word)
{
	uint8_t wordbytes[2] = {(word >> 8) & 0xFF, word & 0xFF};
	uint8_t crc = generateCRC8(wordbytes, 2);
	return(send16BitWordWithCRC(word, crc));
}

bool Altimeter::readBytes(uint8_t* buf, uint8_t len)
{
	Wire.requestFrom((unsigned char)ALTIMETER_ADDRESS, (unsigned char)(len+1));
	if(Wire.available() >= len+1)
	{
		for(int i=0; i<len; i++)
		{
			buf[i] = Wire.read();
			DEBUGSERIAL.printf("rec b%u: %x ",i, buf[i]);
		}
		uint8_t crc = Wire.read();
		DEBUGSERIAL.printf("rec crc: %x ", crc);
		if(generateCRC8(buf, len) != crc)
		{
			DEBUGSERIAL.printf("Altimeter CRC ERROR!\n");
			return false;
		}
		return true;
	}
	return false;
}

uint8_t Altimeter::generateCRC8(const uint8_t *bytes, uint8_t length)
{
	return CRC8.generic(0x31, 0xFF, CRC_FLAG_NOREFLECT, bytes, length);
}
