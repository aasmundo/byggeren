/*
 * MCP2515.c
 *
 * Created: 22.09.2014 14:31:55
 *  Author: aasmundo
 */ 
#include "MCP2515.h"
#include "SPI.h"
#include "CAN.h"

uint8_t MCP2515_read(uint8_t address)
{
	SPI_CS_low();
	SPI_data(0x03);
	SPI_data(address);
	uint8_t temp = SPI_data(address);
	SPI_CS_high();
	return temp;
}

/*
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
	SPI_data(instruction);
	for(int i=0;i<13;i++)
	{
		msg.array[i] = SPI_data(instruction);
	}
	SPI_CS_high();
	return msg;
}*/

union can_msg_t MCP2515_RX_read(uint8_t RX_num)
{
	volatile union can_msg_t mesg = {{0}};
	volatile union can_msg_t mesg_tx = {{0}};	
	//SPI_CS_low();
	if(RX_num == 0){
		
		//READ RX BUFFER
		SPI_CS_low();
			SPI_data(0x03);
			SPI_data(0b01100001);
			for(int i = 0; i < 13; i++){
				mesg.array[i] = SPI_data(0b01100001+i);
			}
		SPI_CS_high();
		
		
		mesg.package.id = ((mesg.array[0] << 8 ) | (mesg.array[1]))>> 5 & 0x7FF;
		mesg.package.dlc &= 0x0F;
		
		//READ OLD TX BUFFER
		SPI_CS_low();
			SPI_data(0x03);
			SPI_data(0b00110001);
			for(int i = 0; i < 13; i++){
				mesg_tx.array[i] = SPI_data(0x00);
			}
		SPI_CS_high();
		
		MCP2515_write(0x2C, 0x00);
		
		mesg_tx.package.id = ((mesg_tx.array[0] << 8) | (mesg_tx.array[1]))>> 5 & 0x7FF;
		//mesg_tx.package.dlc &= 0x0F;
		
	}
	else if(RX_num == 1){
		mesg.package.id = ((MCP2515_read(0b01110001) << 8 )|  (MCP2515_read(0b01110010)) >> 5)& 0x7FF;
		mesg.package.dlc = MCP2515_read(0x75) & 0x0F;
	}
	
	
	//SPI_CS_high();
	return mesg;
}
	

void MCP2515_write(uint8_t address, uint8_t data)
{
	SPI_CS_low();
	SPI_data(0x02);
	SPI_data(address);
	SPI_data(data);
	SPI_CS_high();
}
void MCP2515_RTS(uint8_t register_number)  //request to send
{
	register_number = 0b10000000 + (1<<register_number);
	SPI_CS_low();
	SPI_data(register_number);
	SPI_CS_high();
}

uint8_t MCP2515_RSI()	//Read status instruction
{
	SPI_CS_low();
	SPI_data(0xA0);
	SPI_data(0x00);
	uint8_t temp = SPI_data(0x00);
	SPI_CS_high();
	return temp;
}

void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data)
{
	SPI_CS_low();
	SPI_data(0x05);
	SPI_data(address);
	SPI_data(mask);
	SPI_data(data);
	SPI_CS_high();
}

void MCP2515_reset()
{
	SPI_CS_low();
	SPI_data(0b11000000);
	SPI_CS_high();
}