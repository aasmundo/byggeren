/*
 * menu.h
 *
 * Created: 15.09.2014 17:11:48
 *  Author: jonkol
 */ 


#ifndef MENU_H_
#define MENU_H_
#include <stdint.h>
#include "pong_game.h"

#define max_submenus 4
#define menu_print  0
#define highscore_print  1
#define in_game_print  2
#define reset_print  3
#define game_over_print  4
#define about_print  5
#define name_set_print  6


struct menu  
{
	char *title;
	uint8_t num_submenus;
	struct menu *submenu[max_submenus];
	struct menu *prev_menu;
	uint8_t print_type;
};

struct highscore_entry
{
	char *name;
	uint16_t time;
	
};

struct highscore
{
	struct highscore_entry entries[3];
	
};


void create_menu();
void menu_init();
void print_menu();
void menu_up_or_down(int up_down);
void menu_enter();
struct menu *add_menu(char *name, struct menu *parent, uint8_t print_value);
void print_game_over();
void reset_highscore();
uint8_t menu_dirty_disp();
void menu_animation();
uint8_t menu_is_animation();

#endif /* MENU_H_ */