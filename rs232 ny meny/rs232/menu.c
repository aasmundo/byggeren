/*
 * menu.c
 *
 * Created: 15.09.2014 17:11:39
 *  Author: jonkol
 */ 
#include "menu.h"
#include "OLED.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint8_t arrow_pos = 1; 
struct menu *current_menu;
uint8_t start = 0;
uint8_t stop = 7;

void menu_init()
{
	TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
	TIMSK |= (1 << OCIE1A); // Enable CTC interrupt
	OCR1A = 40000; // Set CTC compare value to 1Hz at 1MHz AVR clock, with a prescaler of 64
	TCCR1B |= ((1 << CS10) | (1 << CS11)); // Start timer at Fcpu/64
}

void menu_up_or_down(int up_down)
{
	//uint8_t last_pos = arrow_pos;
	arrow_pos += up_down;
	if(arrow_pos >=current_menu->num_submenus)
	{
		//arrow_pos = last_pos;
		arrow_pos = 0;
	}
}

void create_menu(){
	struct menu *main_menu;
	struct menu *submenu1, *submenu2, *submenu3, *submenu4, *submenu5, *submenu6, *submenu7, *submenu8, *submenu9, *submenu10, *submenu11;
	struct menu *not_true, *not_false;
	main_menu = malloc(sizeof(struct menu));
	submenu1 =  malloc(sizeof(struct menu));
	submenu2 =  malloc(sizeof(struct menu));
	submenu3 =  malloc(sizeof(struct menu));
	submenu4 =  malloc(sizeof(struct menu));
	submenu5 =  malloc(sizeof(struct menu));
	submenu6 =  malloc(sizeof(struct menu));
	submenu7 =  malloc(sizeof(struct menu));
	submenu8 =  malloc(sizeof(struct menu));
	submenu9 =  malloc(sizeof(struct menu));
	submenu10 =  malloc(sizeof(struct menu));
	submenu11 =  malloc(sizeof(struct menu));
	//not_false =  malloc(sizeof(struct menu));
	//not_true =  malloc(sizeof(struct menu));
	
	main_menu->title = "Main menu\n";
	main_menu->num_submenus = 11;
	
	
	main_menu->submenu[0] = submenu1;
	main_menu->submenu[1] = submenu2;
	main_menu->submenu[2] = submenu3;
	main_menu->submenu[3] = submenu4;
	main_menu->submenu[4] = submenu5;
	main_menu->submenu[5] = submenu6;
	main_menu->submenu[6] = submenu7;
	main_menu->submenu[7] = submenu8;
	main_menu->submenu[8] = submenu9;
	main_menu->submenu[9] = submenu10;
	main_menu->submenu[10] = submenu11;
	
	submenu1->title = "Aasmund er kul\n";
	submenu1->num_submenus = 1;
	submenu1->submenu[0] = main_menu;
	submenu2->title = "Gunnarliker is\n";
	submenu2->num_submenus = 1;
	submenu2->submenu[0] = main_menu;
	submenu3->title = "Jonlikerdumle\n";
	submenu3->num_submenus = 1;
	submenu3->submenu[0] = main_menu;
	submenu4->title = "Jonspiserfisk\n";
	submenu4->num_submenus = 1;
	submenu4->submenu[0] = main_menu;
	submenu5->title = "Gunnar <3casio\n";
	submenu5->num_submenus = 1;
	submenu5->submenu[0] = main_menu;
	submenu6->title = "Aasmunderbest\n";
	submenu6->num_submenus = 1;
	submenu6->submenu[0] = main_menu;
	submenu7->title = "Daddy cool\n";
	submenu7->num_submenus = 1;
	submenu7->submenu[0] = main_menu;
	submenu8->title = "Pete Thorton\n";
	submenu8->num_submenus = 1;
	submenu8->submenu[0] = main_menu;
	submenu9->title = "Sunny\n";
	submenu9->num_submenus = 1;
	submenu9->submenu[0] = main_menu;
	submenu10->title = "Ma Baker\n";
	submenu10->num_submenus = 1;
	submenu10->submenu[0] = main_menu;
	submenu11->title = "Aasmund=n00b\n";
	submenu11->num_submenus = 1;
	submenu11->submenu[0] = main_menu;
	/*
	not_false->title = "Riktig svar! \n";
	not_false->num_submenus = 1;
	not_false->submenu[0] = main_menu;
	
	not_true->title = "Feil\n";
	not_true->num_submenus = 1;
	not_true->submenu[0] = main_menu;
	
	*/
	current_menu = main_menu;

}

void print_menu(){
	
	clear_oled();
	oled_address_reset();
	oled_string_print(current_menu->title);
	
	
	
	if(current_menu->num_submenus <8)
	{
		start = 0;
		stop = (current_menu->num_submenus);
	}else
	{
		if(arrow_pos<start)
		{
			start = arrow_pos;
			stop = start + 7;
		}else if(arrow_pos>=stop)
		{
			stop = arrow_pos+1;
			start = stop - 7;
		}
	}
	//printf("start: %i, stop: %i, arrow_pos: %i \n", start, stop, arrow_pos);

	for(int i = start; i < stop; i++){
		if(arrow_pos == i){
			oled_char_print((char) 30);
		}
		else{
			oled_char_print(' ');
		}	
		
		oled_string_print(current_menu->submenu[i]->title);
	
	}
}


void picture_print(uint8_t picture)
{
	oled_address_reset();
	picture = picture * 128;
	for(int i = 0; i < 128; i++)
	{
		oled_print_graphics((i + picture));	
	}
}

void menu_enter()
{
	current_menu = current_menu->submenu[arrow_pos];
	if(current_menu->num_submenus > 7)
	{
		stop = 7;
	}else
	{
		stop = current_menu->num_submenus;
	}
	
	start = 0;
	arrow_pos = 0;
}



