/*
 * node_com.h
 *
 * Created: 16.11.2014 13:51:11
 *  Author: jonkol
 */ 


#ifndef NODE_COM_H_
#define NODE_COM_H_

#include "MCP2515.h"
#include "Arduino.h"
#include <stdint.h>


void node_com_init();
int control(int function);
void receive_data();
void CAN_data_printer();
void joystick_printer();
uint8_t get_state();




#endif /* NODE_COM_H_ */