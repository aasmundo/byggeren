/*
 * pong_game.c
 *
 * Created: 16.11.2014 16:18:59
 *  Author: jonkol
 */ 

#include "pong_game.h"

uint8_t game_state = IN_MENU;
long unsigned int time;
long unsigned int last_time;
uint16_t highscore[3] = {0};
	
void pong_start_game()
{
	game_state = IN_GAME;	
}
	
void pong_game_loop()
{
	if(game_state == IN_MENU)
	{
		time = 0;
	}else if(game_state == IN_GAME)
	{
		time++;
		if(test_bit(PINB,PINB2) == 0)
		{
			game_state = IN_MENU;
			last_time = time;
		}
	}
}



uint8_t pong_get_game_state()
{
	return game_state;
}

uint16_t pong_get_time()
{
	return time;
}

uint16_t pong_get_last_time()
{
	return last_time;
}

uint16_t pong_get_highscore(uint8_t place) // 0= 1st, 1=2nd ...
{
	return highscore[place];
}

