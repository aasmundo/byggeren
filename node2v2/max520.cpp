/*
 * max520.cpp
 *
 * Created: 04.11.2014 15:04:30
 *  Author: aasmundo
 */ 

#include "max520.h"
int last = 0;
long abs_pos = 0;

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
	pinMode(A8, INPUT);
	pinMode(A9, INPUT);
	pinMode(A10, INPUT);
	pinMode(A11, INPUT);
	pinMode(A12, INPUT);
	pinMode(A13, INPUT);
	pinMode(A14, INPUT);
	pinMode(A15, INPUT);
	digitalWrite(A5, HIGH); //enable motor
	digitalWrite(A3, LOW); //reset encoder
	digitalWrite(A3, HIGH);
	digitalWrite(A2, HIGH); //disable encoder output
	digitalWrite(A4, HIGH); //select high bit of encoder
	digitalWrite(A6, HIGH);
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

int16_t motor_get_position()
{
	
	digitalWrite(A2, LOW); //enable encoder output
	digitalWrite(A4, HIGH); //select LSB
	byte bytes[2] = {0};
	for(int i = 0; i<2;i++)
	{
		bytes[i] = digitalRead(A8);
		bytes[i] |= digitalRead(A9) << 1;
		bytes[i] |= digitalRead(A10) << 2;
		bytes[i] |= digitalRead(A11) << 3;
		bytes[i] |= digitalRead(A12) << 4;
		bytes[i] |= digitalRead(A13) << 5;
		bytes[i] |= digitalRead(A14) << 6;
		bytes[i] |= digitalRead(A15) << 7;
		digitalWrite(A4, LOW);
	}
	//Serial.println(bytes[0]);
	digitalWrite(A3, LOW);
	digitalWrite(A3, HIGH); //toggle reset
	digitalWrite(A2,HIGH); //disable encoder output
	int rotations = (((int) bytes[1] << 8) | (0xff & bytes[0]));
	
	//oving8
	Serial.print("Encoder output: ");
	Serial.print(rotations);
	Serial.print(" , integral: ");
	Serial.println(abs_pos);
	
	
	if(rotations >15000 || rotations < -30000)
	{
		abs_pos += last;
		Serial.println("unlikely value");
	}else
	{
		abs_pos += (long) rotations;
		last = rotations;
	}
	return rotations;
}