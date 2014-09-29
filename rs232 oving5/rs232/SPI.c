/*
 * SPI.c
 *
 * Created: 18.09.2014 17:29:17
 *  Author: jonkol
 */ 
#include <avr/io.h>
#include <stdint.h>
#include "uart.h"
#include "SPI.h"
void SPI_master_init()
{
	set_bit(GICR,INT2);
	
	set_bit(DDRB,DDB4);
	SPI_CS_high();
	set_bit(DDRB,DDB5);
	set_bit(DDRB,DDB7);
	
	set_bit(SPCR,SPE);
	set_bit(SPCR,MSTR);
	set_bit(SPCR,SPR0);
}

void SPI_CS_low()
{
	clear_bit(PORTB,PORTB4);
}

void SPI_CS_high()
{
	set_bit(PORTB,PORTB4);
}

void SPI_transmit(uint8_t data)
{
	clear_bit(PORTB,PORTB4);
	SPDR = data;
	while(!(SPSR & (1<<SPIF)))
	{
		
	}
	set_bit(PORTB,PORTB4);
}

uint8_t SPI_data(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)))
	{
		
	}
	return SPDR;
}

