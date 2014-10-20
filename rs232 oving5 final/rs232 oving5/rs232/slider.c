/*
 * slider.c
 *
 * Created: 09.09.2014 16:15:10
 *  Author: jonkol
 */ 
#include <avr/interrupt.h>
#include <avr/io.h>
#include "uart.h"
#include "ADC.h"
#include "joystick.h"
#include "slider.h"

uint8_t left_slider_pos()
{
	ADC_read(3);
	return ADC_last_value(3);
}

uint8_t right_slider_pos()
{
	ADC_read(4);
	return ADC_last_value(4);
}