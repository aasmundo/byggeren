/*
 * CAN.c
 *
 * Created: 23.09.2014 11:29:59
 *  Author: aasmundo
 */ 
#include "CAN.h"
#include "MCP2515.h"
#include "uart.h"

#define MCP_REG_RXF0SIDH	0x00
#define MCP_REG_RXM0SIDH	0b0010000
#define TXB0SIDL			0b00110010
#define TXB0SIDH			0x31
#define TXB0DLC				0b00110101
#define TXB0D0				0b00110110
#define CANINTF				0x2C
#define RX1IF				0x01
#define RX0IF				0x00
#define RXB0SIDH			0b01100001
#define RXB1SIDH			0b01110001
#define CANINTE				0x2B
#define CANCTRL				0x0F
#define CANSTAT				0x0E
#define TXB0D0				0b00110110
#define TXB0CTRL			0x30
#define RXB1D0				0b01110110
#define RXB0D0				0b01100110
#define RXB1CTRL			0x70
#define RXB0CTRL			0x60
 

void CAN_init()
{
		MCP2515_reset(); 
		
		MCP2515_bit_modify(CANINTE, 0b00000011, 0b11111111); //skrur på RX buffer interrupt
		//MCP2515_bit_modify(TXB0CTRL, 0b00000011, 0b11111111); //setter prio til highest message priority
		MCP2515_bit_modify(RXB0CTRL, 0b01100100, 0b11111111); //skrur av filtrering av mottatte meldinger og setter paa rx0 til rx1 overflow
		MCP2515_bit_modify(RXB1CTRL, 0b01100000, 0b11111111); // skrur av filtrering for rx1
		//MCP2515_bit_modify(CANCTRL, 0b11100000, 0b01000000); //setter i loopback mode
		MCP2515_bit_modify(CANCTRL, 0b11100011, 0b00000011); //setter i normal mode
		printf("CAN initialized \n");
		
		
}


void CAN_send(union can_msg_t msg)
{
	uint16_t temp = msg.package.id << 13;
	uint8_t ID_bits = temp >> 8;
	MCP2515_write(TXB0SIDL,ID_bits & 0xE0);
	volatile uint8_t lol = MCP2515_read(TXB0SIDL);
	ID_bits = msg.package.id >> 3;
	MCP2515_write(TXB0SIDH,ID_bits);
	lol = MCP2515_read(TXB0SIDH);
	MCP2515_write(TXB0DLC,msg.package.dlc & 0x0F);
	lol = MCP2515_read(TXB0DLC);
	
	for(uint8_t i=0;i<msg.package.dlc;i++)
	{
		MCP2515_write(TXB0D0 + i, msg.package.data[i]);
	}
	lol = MCP2515_read(TXB0DLC);
	MCP2515_RTS(0);	
}

union can_msg_t CAN_receive()
{
	uint8_t CANINTF_copy = MCP2515_read(CANINTF);
	uint8_t RX_num;
	if(test_bit(CANINTF_copy, RX0IF))
	{
		RX_num = 0;
	}else if(test_bit(CANINTF_copy, RX1IF))
	{
		RX_num = 1;
	}else
	{
		printf("Error, INT2, ingen av int flaggene i CAN var satt :S, %x \n", CANINTF_copy);
	}
	
	return MCP2515_RX_read(RX_num);
}



