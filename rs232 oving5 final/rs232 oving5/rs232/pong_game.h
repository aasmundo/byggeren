/*
 * pong_game.h
 *
 * Created: 16.11.2014 16:19:10
 *  Author: jonkol
 */ 


#ifndef PONG_GAME_H_
#define PONG_GAME_H_

#include <stdint.h>
#include <avr/io.h>
#include "uart.h"
#define IN_MENU 0
#define IN_GAME 1


void pong_game_loop();
void pong_update_highscore();
uint8_t pong_get_game_state();
uint16_t pong_get_time();
uint16_t pong_get_highscore(uint8_t place);
void pong_start_game();




#endif /* PONG_GAME_H_ */