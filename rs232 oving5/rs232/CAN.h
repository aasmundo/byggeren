/*
 * CAN.h
 *
 * Created: 23.09.2014 11:30:11
 *  Author: aasmundo
 */ 


#ifndef CAN_H_
#define CAN_H_
#include <stdint.h>

typedef struct can_struct_t{
	uint16_t id;
	uint16_t eid;
	uint8_t dlc;
	uint8_t data[8];
};

typedef union can_msg_t{
	struct can_struct_t package;
	uint8_t array[13];
};


struct CAN_struct{
	uint8_t ID;
	uint8_t length;
	uint8_t *data;
	
	};

void CAN_init();
void CAN_send(union can_msg_t msg);
union can_msg_t CAN_receive();

#endif /* CAN_H_ */