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

volatile uint8_t animation_counter = 0;
volatile uint8_t animation = 2;
volatile uint8_t dirty_disp = 0;
volatile int arrow_pos = 0; 
struct menu *current_menu;
uint8_t start = 0;
uint8_t stop = 7;
volatile int char_pos = 65; // char_pos = 'A'
volatile int current_char = 0; // first char in name, char 1 of 3
char name[4];

uint8_t first_game_print = 1;

void menu_init()
{
	TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
	TIMSK |= (1 << OCIE1A); // Enable CTC interrupt
	OCR1A = 1600; // Set CTC compare value to 1Hz at 1MHz AVR clock, with a prescaler of 64
	TCCR1B |= ((1 << CS10) | (1 << CS11)); // Start timer at Fcpu/64
}

void menu_up_or_down(int up_down)
{
	if(current_menu->print_type == menu_print){ //menu arrow position

		arrow_pos += up_down;
		if(current_menu->prev_menu == NULL){
			if(arrow_pos >=current_menu->num_submenus)
			{
				arrow_pos = 0;
			}else if(arrow_pos < 0)
			{
				arrow_pos = current_menu->num_submenus-1;
			}	
		}
		else{
			if(arrow_pos >=current_menu->num_submenus+1)
			{
				
				arrow_pos = 0;
			}else if(arrow_pos < 0)
			{
				arrow_pos = current_menu->num_submenus;
			}
		}
	}
	else if(current_menu->print_type == name_set_print){ //name input
		char_pos += up_down;
		if(char_pos == 64){
			char_pos = 90;
		}
		else if(char_pos == 91){
			char_pos = 65;
		}
		name[current_char] = char_pos;
	}
	dirty_disp = 1;
}

struct highscore *highscore_list;
/*
struct highscore_entry new_highscore_entry(void){
	struct highscore_entry e = malloc(sizeof(struct highscore_entry));
	e->name = malloc(3);
	return e;
}*/


void create_menu(){
	highscore_list = malloc(sizeof(struct highscore)); // create highscore
	
	for(int i = 0; i<3;i++)
	{
		highscore_list->entries[i].name = malloc(4);
		highscore_list->entries[i].name[3] = '\0';
	}

	reset_highscore();
		name[0] = '_';
		name[1] = '_';
		name[2] = '_';
	
	struct menu *main_menu				= add_menu("Main menu\n", NULL, menu_print);					//current_menu->prev_menu->prev_menu
		struct menu *pong					= add_menu("Ping Pong\n", main_menu, menu_print);
			struct menu *new_game				= add_menu("New game\n", pong, in_game_print);			// game over til new name
			struct menu *highscore_menu			= add_menu("Highscore\n", pong, highscore_print);
					struct menu *new_name			= add_menu("name\n", highscore_menu, name_set_print);
				struct menu *game_over				= add_menu("Game finished\n", new_game, game_over_print);
			struct menu *reset_score			= add_menu("Reset highscore\n", pong, reset_print);
			
		struct menu *about					= add_menu("About\n", main_menu, about_print);
	dirty_disp = 1;	

}
void what_to_print(){ //
	//printf(current_menu->title);
	
	if(current_menu->print_type == menu_print) print_menu();
	else if(current_menu->print_type == in_game_print) print_in_game();
	else if(current_menu->print_type == highscore_print) print_highscore();
	else if(current_menu->print_type == about_print) print_about();
	else if(current_menu->print_type == reset_print) print_reset();	
	else if(current_menu->print_type == game_over_print) print_game_over();
	else if(current_menu->print_type == name_set_print) print_set_name();
}

void print_game_over(){
	clear_oled();
	oled_address_reset();
	dirty_disp = 1;
	if(pong_get_last_time() > highscore_list->entries[2].time){
		animation = 0;
	}
	else{
		animation = 1;
	}
}

void print_highscore(){
	if(current_menu->print_type == highscore_print){
		clear_oled();
		oled_address_reset();
	}
	
	
	oled_string_print("Time to beat: \n");
	char temp_time[10] = "         \n";
	char num[2];
	for(int i=0;i<3;i++)
	{
		sprintf(num, "%d", (i+1));
		oled_string_print_length(num,1);
		oled_string_print_length(". ", 2);
		oled_string_print_length(highscore_list->entries[i].name, 3);
		oled_char_print(' ');
		sprintf(temp_time, "%d", highscore_list->entries[i].time);
		oled_string_print_length(temp_time,9);
		oled_char_print('\n');
		strcpy(temp_time, "         \n");
	}
	
	if(current_menu->print_type == highscore_print){
		oled_char_print((char) 30);
		oled_string_print("Back\n");
	}
	
}

void print_in_game(){
	if(first_game_print == 1)
	{
		first_game_print = 0;
		clear_oled();
		oled_address_reset();
		oled_string_print("Current time:\n");
		char temp_time[16] = "               \n";
		sprintf(temp_time, "%d", pong_get_time());
		oled_string_print(temp_time);
		print_highscore();
		printf("for print high\n");
	}else
	{
		
		oled_clear_and_go_to_line(1);
		char temp_time[15] = "              \n";
		sprintf(temp_time, "%d", pong_get_time());
		oled_string_print_length(temp_time,13);
	}
	
	
	if(pong_get_game_state() == IN_MENU) {
		current_menu = current_menu->submenu[0]; //= game over
		first_game_print = 1;
		dirty_disp = 1;
	}
}

void print_set_name(){
	clear_oled();
	oled_address_reset();
	oled_string_print("Congratulations!\n");
	oled_string_print_length("Enter name: ", 12);
	oled_string_print_length(name, 3);
}
void print_about(){
	clear_oled();
	oled_address_reset();
	oled_string_print("Made by: \n");
	oled_string_print("Åsmund\n");
	oled_string_print("Gunnar\n");
	oled_string_print("Jon\n");
	
}

void print_reset(){
	clear_oled();
	oled_address_reset();
	if(highscore_list->entries[0].time == 0){
		oled_string_print("Highscore\n");
		oled_string_print("already reset\n");
	}
	else{
		oled_string_print("Highscore \n");
		oled_string_print("has been reset\n");
	}
	
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
	animation_counter = 0;
	animation = 2;
	if(current_menu->print_type == menu_print){ 
		if (arrow_pos == current_menu->num_submenus){// go back in menu
			current_menu = current_menu->prev_menu;
		}
		else if(current_menu->num_submenus != 0){ // enter submenu
		
			current_menu = current_menu->submenu[arrow_pos];
			if(current_menu->print_type == in_game_print)
			{
				
				pong_start_game();
				first_game_print = 1;
			}
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
	else if(current_menu->print_type == name_set_print) {	// confirm name char
		name[current_char] = char_pos;
		
		if(current_char == 2){ //stop name input, show highscore
			
			update_highscore(pong_get_last_time());
			
			current_menu = current_menu->prev_menu; // = highscore
			current_char = 0;
			char_pos = 65;
			
		}else{
		current_char += 1;
		char_pos = 65;
		name[current_char] = char_pos;
		}
	}
	else if(current_menu->print_type == game_over_print){
		if(pong_get_last_time() > highscore_list->entries[2].time){
			current_menu = current_menu->prev_menu->prev_menu->submenu[1]->submenu[0];  // = new_name  må mulig fikses
		}
		else{
			current_menu = current_menu->prev_menu->prev_menu->submenu[1]; // = highscore
		}
	}  
	else if(current_menu->print_type != in_game_print ){
		current_menu = current_menu->prev_menu; // else go back to previous menu
	}
	dirty_disp = 1;
}


struct menu *add_menu(char *name, struct menu *parent, uint8_t print_value){
	struct menu *new_menu = malloc(sizeof(struct menu));
	new_menu->title = name;
	new_menu->num_submenus = 0;
	new_menu->prev_menu = parent;
	new_menu->print_type = print_value;
	
	if(parent != NULL){
		parent->submenu[parent->num_submenus] = new_menu;
		parent->num_submenus += 1;
		
	}
	else{
		current_menu = new_menu;
	}
	return new_menu;
}

void update_highscore(uint8_t new_time){
	if (pong_get_last_time() > highscore_list->entries[0].time){ //If new first place
		
		highscore_list->entries[2].time = highscore_list->entries[1].time;
		strcpy(highscore_list->entries[2].name, highscore_list->entries[1].name);
		highscore_list->entries[1].time = highscore_list->entries[0].time;
		strcpy(highscore_list->entries[1].name, highscore_list->entries[0].name);
		highscore_list->entries[0].time = pong_get_last_time();
		strcpy(highscore_list->entries[0].name, name);		
	}
	else if(pong_get_last_time() > highscore_list->entries[1].time){ // IF new second place
		highscore_list->entries[2].time = highscore_list->entries[1].time;
		strcpy(highscore_list->entries[2].name, highscore_list->entries[1].name);
		highscore_list->entries[1].time = pong_get_last_time();
		strcpy(highscore_list->entries[1].name, name);
		
	}
	else if(pong_get_last_time() > highscore_list->entries[2].time){ // If new third place
		highscore_list->entries[2].time = pong_get_last_time();
		strcpy(highscore_list->entries[2].name, name);
	}
	
	//name = "___ \n"; // Reset name to blank for next name input
	name[0] = '_';
	name[1] = '_';
	name[2] = '_';
	name[3] = '\0';
	
}

void reset_highscore(){
	for(int i=0; i<3;i++)
	{
		highscore_list->entries[i].time = 0;
		strcpy(highscore_list->entries[i].name, "N/A");
	}

}

uint8_t menu_dirty_disp()
{
	if(dirty_disp == 0)
	{
		return 0;
	}else
	{
		dirty_disp = 0;
		return 1;	
	}
}

uint8_t menu_is_animation()
{
	if(animation < 2)
	{
		return 1;
	}
	return 0;
}

void menu_animation()
{
	
	if(animation == 0)
	{
		dirty_disp = 1;
		if(animation_counter == 1)
		{
			oled_print_picture(0);
		}else if(animation_counter == 11)
		{
			oled_print_picture(1);
		}else if(animation_counter == 21)
		{
			oled_print_picture(2);
		}else if(animation_counter == 30)
		{
			animation_counter = 0;
		}
		animation_counter++;
		return 1;
	}else if(animation == 1)
	{
		dirty_disp = 1;
		if(animation_counter == 1)
		{
			oled_print_picture(3);
		}else if(animation_counter == 11)
		{
			oled_print_picture(4);
		}else if(animation_counter == 21)
		{
			oled_print_picture(5);
		}else if(animation_counter == 30)
		{
			animation_counter = 0;
		}
		animation_counter++;
		return 1;
	}
	return 0;
}