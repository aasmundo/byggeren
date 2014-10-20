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

volatile long int timer = 0;
volatile uint8_t cool_down = 0;
volatile uint8_t dirty_display = 1;
volatile uint8_t CAN_ready = 0;
int main(void)
{
	set_bit(DDRB,DDB0);
	SPI_master_init();
	//SPI_transmit(0xAA);
	USART_Init(MYUBRR);
	Enable_UAR0_Interrupt();
	SRAM_init();
	ADC_init();
	joy_button_init();
	oled_init();
	menu_init();
	create_menu();
	CAN_init();
	
	/*
	SPI_CS_low();
	volatile uint8_t test = (SPI_data(0b00110111));*/
	
	union can_msg_t message;
	message.package.id = 0x04FF;
	message.package.dlc = 8;
	message.package.eid = 0x0000;
	for(int i = 0; i<8; i++)
	{
		message.package.data[i] = i;
	}
	
	CAN_send(message);
	while(1)
	{
		
		
		_delay_ms(10);
		if(CAN_ready==1)
		{
			CAN_ready = 0;
			union can_msg_t temp = CAN_receive();
			for(int i = 0; i<13;i++)
			{
				printf(" linje %i: %i \n",i,temp.array[i]);
			}
		}
		_delay_ms(1000);
	}

}
/* timer interrupt ~50hz */
ISR(TIMER1_COMPA_vect)
{
	PORTB ^= 0x01; // Toggle the LED
	if(cool_down == 1 && timer <12)
	{
		timer++;
	}else
	{
		timer = 0;
		cool_down = 0;
	}
	if(ADC_busy() == 0)
	{
		if(dirty_display != 0)
		{
			print_menu();
			dirty_display = 0;
		}
		y_pos();	
	}
	
}
/* ADC interrupt */
ISR(INT0_vect){
	volatile char *ext_adc = (char *) 0x1403;
	if(cool_down == 0)
	{
		if(ext_adc[0] < 10)
		{
			menu_up_or_down(1);
			cool_down = 1;
			timer = 0;
			dirty_display = 1;
		}else if(ext_adc[0]>245)
		{
			menu_up_or_down(-1);
			cool_down = 1;
			timer = 0;
			dirty_display = 1;
		}
	}
	
	ADC_busy(0);
}
/* jOYSTICK BUTTON */
ISR(INT1_vect){

	if(cool_down == 0)
	{
		menu_enter();
		cool_down = 1;
		timer = 0;
		dirty_display = 1;
	}
	
	return;
}

/* CAN INTERRUPT */
ISR(INT2_vect){
	CAN_ready = 1;

}