#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"

volatile uint8_t last_read = 1;
volatile uint8_t busy = 0;
volatile unsigned char MA[4];


uint8_t ADC_last_read_input()
{
	return last_read;
}

uint8_t ADC_busy()
{
	return busy;
}

void ADC_set_busy_state(uint8_t state)
{
	busy = state;
}

unsigned char ADC_last_value(int chan)
{
	return MA[chan - 1];
}

void ADC_init(){
	set_bit(GICR, INT0);
	set_bit(MCUCR, ISC01);
	clear_bit(MCUCR, ISC00);
	sei();
	printf("ADC initialized \n");
}





void ADC_read(char chan){	
	if(chan < 1 || chan > 4){
		printf("error: no such adc channel: %i \n", chan);
		return;
	}
	ADC_busy(1);
	volatile char *ext_adc = (char *) 0x1400; //TODO: get from some header file
	ext_adc[0] = 0x03 + chan;
	last_read = chan;		
}