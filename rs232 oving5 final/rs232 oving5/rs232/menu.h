/*
 * menu.h
 *
 * Created: 15.09.2014 17:11:48
 *  Author: jonkol
 */ 


#ifndef MENU_H_
#define MENU_H_
#include <stdint.h>

#define max_title_len 15
#define max_submenus 15
struct menu
{

	char *title;//[max_title_len];
	uint8_t num_submenus;
	struct menu *submenu[max_submenus];
	struct menu *prev_menu;
};
void create_menu();
void menu_init();
void print_menu();
void menu_up_or_down(int up_down);
void menu_enter();
struct menu *add_menu(char *name, struct menu *parent);


#endif /* MENU_H_ */