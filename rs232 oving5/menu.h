/*
 * menu.h
 *
 * Created: 15.09.2014 17:19:13
 *  Author: gunnalid
 */ 


#ifndef MENU_H_
#define MENU_H_

#define max_title_len 16
#define max_submenus 7
struct menu
{

	char title[max_title_len];
	void (*command)();
	int num_submenus;
	struct menu *submenu[max_submenus];
};

//testtest

#endif /* MENU_H_ */