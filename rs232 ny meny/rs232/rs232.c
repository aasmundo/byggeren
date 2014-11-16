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
//#include "font.h"

volatile long int timer = 0;
volatile uint8_t cool_down = 0;
volatile uint8_t dirty_display = 1;

volatile uint8_t frame = 0;
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
	//create_menu();

	while(1)
	{
			MCP2515_read(31);
	}

}

ISR(TIMER1_COMPA_vect)
{
	PORTB ^= 0x01; // Toggle the LED
	
	picture_print(frame);
	printf("%i \n", frame);
	if(frame == 1)
	{
		frame = 0;
	}else
	{
		frame++;
	}
	
	if(cool_down == 1 && timer <15)
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
			
			dirty_display = 0;
		}
		y_pos();	
	}
	
}

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
	
}