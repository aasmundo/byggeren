/*
 * MCP2515.h
 *
 * Created: 22.09.2014 14:32:04
 *  Author: aasmundo
 */ 


#ifndef MCP2515_H_
#define MCP2515_H_
#include <avr/io.h>
#include <stdint.h>

uint8_t MCP2515_read(uint8_t address);
void MCP2515_write(uint8_t address, uint8_t data);
void MCP2515_RTS(uint8_t instruction);
uint8_t MCP2515_RSI();


#endif /* MCP2515_H_ */