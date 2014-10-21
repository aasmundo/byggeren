/*
 * MCP2515.c
 *
 * Created: 22.09.2014 14:31:55
 *  Author: aasmundo
 */ 
#include "MCP2515.h"
#include "SPI_driver.h"

#define CANINTF 0x2C
#define CANINTE 0x2B


uint8_t MCP2515_read(uint8_t address)
{
	SPI_CS_low();
	SPI.transfer(0x03);
	SPI.transfer(address);
	uint8_t temp = SPI.transfer(address);
	SPI_CS_high();
	return temp;
}

union can_msg_t MCP2515_RX_read(uint8_t RX_num)
{
	union can_msg_t msg;
	uint8_t instruction;
	if(RX_num = 0)
	{
		instruction = 0b10010000;
	}else
	{
		instruction = 0b10010100;
	}
	SPI_CS_low();
	SPI.transfer(instruction);
	for(int i=0;i<13;i++)
	{
		msg.array[i] = SPI.transfer(instruction);
	}
	SPI_CS_high();
	MCP2515_bit_modify(CANINTF,0b11111100, 0x00);
	return msg;
}

void MCP2515_write(uint8_t address, uint8_t data)
{
	SPI_CS_low();
	SPI.transfer(0x02);
	SPI.transfer(address);
	SPI.transfer(data);
	SPI_CS_high();
}
void MCP2515_RTS(uint8_t register_number)  //request to send
{
	register_number = 0b10000000 + (1<<register_number);
	SPI_CS_low();
	SPI.transfer(register_number);
	SPI_CS_high();
}

uint8_t MCP2515_RSI()	//Read status instruction
{
	SPI_CS_low();
	SPI.transfer(0xA0);
	SPI.transfer(0x00);
	uint8_t temp = SPI.transfer(0x00);
	SPI_CS_high();
	return temp;
}

void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data)
{
	SPI_CS_low();
	SPI.transfer(0x05);
	SPI.transfer(address);
	SPI.transfer(mask);
	SPI.transfer(data);
	SPI_CS_high();
}

void MCP2515_reset()
{
	SPI_CS_low();
	SPI.transfer(0b11000000);
	SPI_CS_high();
}
