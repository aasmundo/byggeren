/*
 * menu.c
 *
 * Created: 15.09.2014 17:18:59
 *  Author: gunnalid
 */ 
#include "menu.h"


void create_menu(){
	struct menu *main_menu;
	*main_menu->title = "Main menu";
	main_menu->num_submenus = 3;
	
	
	*main_menu->submenu[0]->title = "Aasmund er homo!";
	*main_menu->submenu[1]->title = "Gunnar er homo!";
	*main_menu->submenu[2]->title = "Jon er homo!";
	
	oled_address_reset();
	printf(main_menu->title + '\n');
	printf(main_menu->submenu[0]->title + '\n');
	printf(main_menu->submenu[1]->title + '\n');
	printf(main_menu->submenu[2]->title + '\n');
	
}

