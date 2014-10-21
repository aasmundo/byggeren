/*
 * rs232.c
 *
 * Created: 27.08.2014 16:05:57
 *  Author: jonkol & Oma
 */ 
#define F_CPU 4915200
//#define F_CPU 614400

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "sram_driver.h" 
#include "ADC.h"
#include "joystick.h"
#include "slider.h"
#include "OLED.h"
#include "menu.h"
#include "SPI.h"
#include "MCP2515.h"
#include "CAN.h"
//#include "font.h"

volatile uint8_t toggler = 0;
volatile uint8_t button_pressed = 0;
volatile union can_msg_t message;
volatile uint8_t CAN_data_waiting = 0;
volatile uint8_t CAN_send_ready = 0;
int main(void)
{
	set_bit(DDRB,DDB0);
	SPI_master_init();
	//SPI_transmit(0xAA);
	USART_Init(MYUBRR);
	Enable_UAR0_Interrupt();
	SRAM_init();
	ADC_init();
	menu_init();
	joy_button_init();
	CAN_init();
	

	
	
	message.package.id = 0x001;
	message.package.dlc = 3;
	message.package.eid = 0x0000;
	
	//CAN_send(message);
	while(1)
	{
		
		
		//_delay_ms(1000);
		if(CAN_data_waiting ==1)
		{
			CAN_data_waiting = 0;
			union can_msg_t temp = CAN_receive();
			for(int i = 0; i<13;i++)
			{
				printf(" linje %i: %i \n",i,temp.array[i]);
			}
		}else if(CAN_send_ready == 1)
		{
			CAN_send(message);
			CAN_send_ready = 0;
		}
	}

}
/* timer interrupt ~50hz */
ISR(TIMER1_COMPA_vect)
{
	PORTB ^= 0x01; // Toggle the LED
	
	if(ADC_busy() == 0)
	{
		if(toggler == 0)
		{
			y_pos();
		}else if(toggler == 1)
		{
			x_pos();
		}else
		{
			toggler = 0;
			message.package.data[2] = button_pressed;
			button_pressed = 0;
			CAN_send_ready = 1;	
		}
			
	}
	
}
/* ADC interrupt */
ISR(INT0_vect){
	volatile char *ext_adc = (char *) 0x1403;
	message.package.data[toggler] = ext_adc[0];
	toggler++;
	ADC_busy(0);
}
/* jOYSTICK BUTTON */
ISR(INT1_vect){

	button_pressed = 1;
	
	return;
}

/* CAN INTERRUPT */
ISR(INT2_vect){
	CAN_data_waiting = 1;

}