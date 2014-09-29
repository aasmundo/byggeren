/*
 * OLED.c
 *
 * Created: 11.09.2014 13:34:01
 *  Author: jonkol
 */ 
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include "uart.h"
#include "ADC.h"
#include "joystick.h"
#include "font.h"
#include "OLED.h"

uint8_t *oled_settings = (uint8_t *) 0x1000;
uint8_t *oled_display_memory = (uint8_t *) 0x1200;
uint8_t line, column;
/*
volatile uint8_t *frame_buffer = (uint8_t *) 0x1800;
*/
void write_c(uint8_t setting)
{
	oled_settings[setting] = setting;
}

void oled_init()
{
		write_c(0xae); // display off
		write_c(0xa1); //segment remap
		write_c(0xda); //common pads hardware: alternative
		write_c(0x12);
		write_c(0xc8); //common output scan direction:com63~com0
		write_c(0xa8); //multiplex ration mode:63
		write_c(0x3f);
		write_c(0xd5); //display divide ratio/osc. freq. mode
		write_c(0x80);
		write_c(0x81); //contrast control
		write_c(0x50);
		write_c(0xd9); //set pre-charge period
		write_c(0x21);
		write_c(0x20); //Set Memory Addressing Mode
		write_c(0x02);
		write_c(0xdb); //VCOM deselect level mode
		write_c(0x30);
		write_c(0xad); //master configuration
		write_c(0x00);
		write_c(0xa4); //out follows RAM content
		write_c(0xa6); //set normal display
		write_c(0xAF); // display on
		clear_oled();
		oled_address_reset();
		printf("oled initialized \n");
}
/*
void print_to_frame_buffer(uint8_t pixels, uint16_t pos)
{
	frame_buffer[pos] = pixels;
}

void print_from_frame_buffer()
{
	for(int k=0; k<8;k++)
	{
		oled_clear_and_go_to_line(k);
		for(int i=0;i<128;i++)
		{
			oled_write(frame_buffer[i]);
		}
	}
	
}
*/

void clear_oled()
{
	for(int i=0; i < 8;i++)
	{
		oled_clear_and_go_to_line(i);
	}
}

void oled_write(uint8_t data)
{
	oled_display_memory[0] = data;
}

void oled_char_print(char letter)
{
	//uint16_t pixel_pos;
	if(letter != '\n')
	{
		column++;
		if(column == 16)
		{
			column = 0;
			line++;
			if(line == 8)
			{
				line = 0;
			}
			oled_set_column_address(0,127);
			oled_set_page_address(line,7);
		}
		for(int i = 0; i<8; i++)
		{
			oled_write(pgm_read_byte(&font[(int)letter - 30][i]));
			//pixel_pos = i + (column*8) + (line * 128);
			//print_to_frame_buffer(pgm_read_byte(&font[(int)letter - 30][i]), pixel_pos);

		}
	}else
	{
		line++;
		column = 0;
		//oled_set_column_address(0,127);
		oled_go_to_line(line);
	}
	
}

void oled_string_print(char* streng)
{
	
	
	int i = 0;
	while(streng[i] != '\n')
	{	
		oled_char_print(streng[i]);
		i++;
	}
	oled_char_print(streng[i]);
	
}

void oled_set_column_address(uint8_t column_start, uint8_t column_end)
{
	write_c(0x21);
	write_c(column_start);
	write_c(column_end);
}

void oled_set_page_address(uint8_t page_start, uint8_t page_end)
{
	write_c(0x22);
	write_c(page_start);
	write_c(page_end);	
}

void oled_address_reset()
{
	line= 0;
	column = 0;
	oled_set_column_address(0,127);
	oled_set_page_address(0,7);
}



void oled_clear_and_go_to_line(uint8_t line_in)
{
	line = line_in;
	column = 0;
	oled_set_column_address(0,127);
	oled_set_page_address(line,7);
	for(int i=0;i<128;i++)
	{
		oled_write(0x00);
	}
	oled_set_column_address(0,127);
	column = 0;
}
void oled_go_to_line(uint8_t line_in)
{
	line = line_in;
	column = 0;
	oled_set_column_address(0,127);
	oled_set_page_address(line,7);
}

