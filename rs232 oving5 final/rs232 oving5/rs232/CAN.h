/*
 * CAN.h
 *
 * Created: 23.09.2014 11:30:11
 *  Author: aasmundo
 */ 


#ifndef CAN_H_
#define CAN_H_
#include <stdint.h>

typedef struct  {
	uint16_t id;
	uint16_t eid;
	uint8_t dlc;
	uint8_t data[8];
}can_struct_t;

typedef union can_msg_t {
	can_struct_t package;
	uint8_t array[13];
}can_msg_t;




void CAN_init();
void CAN_send(union can_msg_t msg);
union can_msg_t CAN_receive();

#endif /* CAN_H_ */