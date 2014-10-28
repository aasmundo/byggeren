/*
 * Servo.cpp
 *
 * Created: 28.10.2014 12:07:11
 *  Author: jonkol
 */ 
#define F_CPU 16000000
#include "Servo.h"


long cycles;
uint8_t high_low = 1;

void PWM_setup(uint8_t pwm_period)
{
	TCCR3A |= (1<<COM3A1)|(1 << COM3B1) | (1 << WGM31);
	TCCR3B |= (1 << CS31) | (3 << WGM32);
	
	ICR3 = 40000;
	OCR3A = 1800;
	OCR3B = 1800;
}

void PWM(uint16_t duty)
{
	unsigned long dutyCycle = cycles;
	dutyCycle *= duty;
	dutyCycle >>= 10;
	Serial.print(dutyCycle);
	OCR3A = dutyCycle;
}


