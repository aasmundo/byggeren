/*
 * MCP2515.h
 *
 * Created: 22.09.2014 14:32:04
 *  Author: aasmundo
 */ 


#ifndef MCP2515_H_
#define MCP2515_H_
#include <stdint.h>
#include "SPI.h"
#include <SPI>

uint8_t MCP2515_read(uint8_t address);
void MCP2515_write(uint8_t address, uint8_t data);
void MCP2515_RTS(uint8_t register_number);
uint8_t MCP2515_RSI();
void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
void MCP2515_reset();
union can_msg_t MCP2515_RX_read(uint8_t RX_num);

#endif /* MCP2515_H_ */
