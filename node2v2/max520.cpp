/*
 * max520.cpp
 *
 * Created: 04.11.2014 15:04:30
 *  Author: aasmundo
 */ 

#include "max520.h"


void max520_init()
{
	pinMode(A0, OUTPUT);
	pinMode(A1, OUTPUT);
	pinMode(A2, OUTPUT);
	pinMode(A3, OUTPUT);
	pinMode(A4, OUTPUT);
	pinMode(A5, OUTPUT);
	pinMode(A6, OUTPUT);
	pinMode(A7, OUTPUT);
	pinMode(A8, OUTPUT);
	pinMode(A9, OUTPUT);
	pinMode(A10, OUTPUT);
	digitalWrite(A5, HIGH);
	Wire.begin();
	Wire.beginTransmission(0x28);
	Wire.write(0x01);
	Wire.write(0x7f);
	Wire.endTransmission();
}

void max520_set_value(uint8_t value)
{
	Wire.beginTransmission(0x28);
	Wire.write(0x00);
	Wire.write(value);
	Wire.endTransmission();	
}