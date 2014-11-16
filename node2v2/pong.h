/*
 * pong.h
 *
 * Created: 16.11.2014 13:45:18
 *  Author: jonkol
 */ 


#ifndef PONG_H_
#define PONG_H_

#define X 1
#define Y 0
#define SLIDER 2
#define CLICK 3
#define GOAL 4

#define IN_MENU 0
#define INGAME 1
#define GOAL_COOLDOWN 2
#define RESET 3


#include "Servo.h" 
#include "max520.h"
#include "MCP2515.h"
#include "node_com.h"






void pong_init();
int motor_control(uint8_t number);
void pong_loop_this();
void solenoid(int fire);
void pong_data_update();



#endif /* PONG_H_ */