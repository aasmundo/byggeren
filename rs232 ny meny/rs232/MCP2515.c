/*
 * MCP2515.c
 *
 * Created: 22.09.2014 14:31:55
 *  Author: aasmundo
 */ 
#include "MCP2515.h"
#include "SPI.h"

uint8_t MCP2515_read(uint8_t address)
{
	SPI_CS_low();
	SPI_data(0x03);
	SPI_data(address);
	uint8_t temp = SPI_data(address);
	SPI_CS_high();
	return temp;
}

void MCP2515_write(uint8_t address, uint8_t data)
{
	SPI_CS_low();
	SPI_data(0x02);
	SPI_data(address);
	SPI_data(data);
	SPI_CS_high();
}
void MCP2515_RTS(uint8_t instruction)
{
	SPI_CS_low();
	SPI_data(instruction);
	SPI_CS_high();
}

uint8_t MCP2515_RSI()
{
	SPI_CS_low();
	SPI_data(0xA0);
	SPI_data(0x00);
	uint8_t temp = SPI_data(0x00);
	SPI_CS_high();
	return temp;
}