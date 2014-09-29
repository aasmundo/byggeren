/*
 * joystick.c
 *
 * Created: 09.09.2014 13:16:24
 *  Author: jonkol
 */ 

#include <avr/interrupt.h>
#include <avr/io.h>
#include "uart.h"
#include "ADC.h"
#include "joystick.h"

uint8_t button_state = 0;



void joy_button_init()
{
	set_bit(GICR, INT1);
	set_bit(MCUCR, ISC11);
	clear_bit(MCUCR, ISC10);
	sei();
	printf("Joystick button initialized \n");
}

uint8_t unresolved_button_press()
{
	if(button_state == 1) 
	{
		button_state = 0;
		return 1;
	}
	return 0;
}

void x_pos()
{
	ADC_read(2);
}

void y_pos()
{
	ADC_read(1);
}

uint8_t unhandeled_button_press()
{
	return MA3_low_to_high();
}

unsigned char joy_smoothing(unsigned char input)
{
	double temp = (double) input;
	temp = temp - 127.5;
	double tempSquared = temp * temp;
	temp = 0.00003249110626 * tempSquared * temp + 0.4711103115 * temp + 127.5;
	unsigned char result = (unsigned char) round(temp);
	return result;
}