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

void left_slider_pos()
{
	ADC_read(3);
}

void right_slider_pos()
{
	ADC_read(4);
}