/*
 * uart.c
 *
 * Created: 27.08.2014 17:08:25
 *  Author: jonkol
 */ 
#include <avr/io.h>
#include "uart.h"
#include "sram_driver.h"
#include "OLED.h"
#include <avr/interrupt.h>
#include <util/delay.h>
unsigned char tull[50];
unsigned int k = 0;

unsigned char received_data_from_usart; 

void USART_Init(unsigned int ubrr )
{
	/*Set baud rate*/
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter*/
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/*Set frame format: 8data, 2stop bit*/
	UCSR0C = (1<<URSEL0)|(3<<UCSZ00);
	fdevopen(USART0_Transmit, USART0_Receive,0);  //oled_char_print
}

unsigned char USART0_Receive()
{
	//return recived_data_form_usart;
	return received_data_from_usart;
}


void Enable_UAR0_Interrupt()
{
	UCSR0B |= (1<<RXCIE0);
}

void USART0_Transmit( unsigned char chardata )
{
	/* Wait for empty transmit buffer*/
	while( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data*/
	UDR0 = chardata;
}

void USART0_array_transmit( unsigned char* chardata, unsigned int array_length)
{
	for(int i=0;i<array_length;i++)
	{
		if(chardata[i] != '\0')
		{
			USART0_Transmit(chardata[i]);
		}else
		{
			USART0_Transmit('\n');
			return;
		}
		
	}
}

ISR(USART0_RXC_vect) 
 { 
	unsigned char temp = UDR0;
	if(temp != '\n')
	{
		received_data_from_usart = temp;
	}
	
	
	//recived_data_form_usart = UDR0;
	//USART0_Transmit(temp);
	/*
	tull[k] = UDR0;
	
	if(tull[k] != '\n')
	{
		k++;
		return;
	}else
	{
		k++;
		tull[k] = '\n';
		USART0_array_transmit(tull, k);
		k = 0;
	}
	*/
 } 
 


	