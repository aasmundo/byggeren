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
#include <stdlib.h>

volatile int arrow_pos = 0; 
struct menu *current_menu;
uint8_t start = 0;
uint8_t stop = 7;

void menu_init()
{
	TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
	TIMSK |= (1 << OCIE1A); // Enable CTC interrupt
	OCR1A = 1000 ; // Set CTC compare value to 1Hz at 1MHz AVR clock, with a prescaler of 64
	TCCR1B |= ((1 << CS10) | (1 << CS11)); // Start timer at Fcpu/64
}

void menu_up_or_down(int up_down)
{
	//uint8_t last_pos = arrow_pos;
	arrow_pos += up_down;
	if(current_menu->prev_menu == NULL){
		if(arrow_pos >=current_menu->num_submenus)
		{
			//arrow_pos = last_pos;
			arrow_pos = 0;
		}else if(arrow_pos < 0)
		{
			arrow_pos = current_menu->num_submenus-1;
		}	
	}
	else{
		if(arrow_pos >=current_menu->num_submenus+1)
		{
			//arrow_pos = last_pos;
			arrow_pos = 0;
		}else if(arrow_pos < 0)
		{
			arrow_pos = current_menu->num_submenus;
		}
	}
}

void create_menu(){
	struct menu *main_menu = add_menu("Main menu\n", NULL);
		struct menu *sub = add_menu("Aasmund er kul\n", main_menu);
			struct menu *hehe = add_menu("Bare tulla\n", sub);
				add_menu("lol\n", hehe);
			add_menu("gunnarerkulere\n", sub);
			add_menu("jon er kulest\n", sub);
		add_menu("Gunnarliker is\n", main_menu);
		add_menu("Jonlikerdumle\n", main_menu);
		add_menu("Jonspiserfisk\n", main_menu);
		add_menu("hei\n", main_menu);
		add_menu("hallo\n", main_menu);
		add_menu("asdfjkjfsagf\n", main_menu);
		add_menu("menu scroll\n", main_menu);
}

void print_menu(){
	
	clear_oled();
	oled_address_reset();
	oled_string_print(current_menu->title);
	
	
	if(current_menu->prev_menu == NULL && current_menu->num_submenus <8){
		start = 0;
		stop = current_menu->num_submenus;
	}
	else if(current_menu->num_submenus < 7){
		start = 0;
		stop = current_menu->num_submenus+1;
	}
	else
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
	
	for(int i = start; i < stop; i++){
		if(arrow_pos == i){
			oled_char_print((char) 30);
		}
		else{
			oled_char_print(' ');
		}
		
		if(current_menu->submenu[i] == NULL && current_menu->prev_menu != NULL){
			oled_string_print("Back\n");
		}
		else{
			oled_string_print(current_menu->submenu[i]->title);
		}
		
	}

}

void menu_enter()
{	
	if (arrow_pos == current_menu->num_submenus){
		current_menu = current_menu->prev_menu;
	}
	else if(current_menu->num_submenus != 0){
		
		current_menu = current_menu->submenu[arrow_pos];
	}
	if(current_menu->num_submenus > 6)
	{
		stop = 7;
	}else
	{
		stop = current_menu->num_submenus + 1;
	}
	
	start = 0;
	arrow_pos = 0;
}


struct menu *add_menu(char *name, struct menu *parent){
	struct menu *new_menu = malloc(sizeof(struct menu));
	new_menu->title = name;
	new_menu->num_submenus = 0;
	new_menu->prev_menu = parent;
	
	if(parent != NULL){
		parent->submenu[parent->num_submenus] = new_menu;
		parent->num_submenus += 1;
		
	}
	else{
		current_menu = new_menu;
	}
	return new_menu;
}