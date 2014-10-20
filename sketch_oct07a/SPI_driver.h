


#ifndef SPI_H_
#define SPI_H_
#include <stdint.h>
#include <SPI.h>
void SPI_init();
void SPI_CS_high();
void SPI_CS_low();
void SPI_write(uint8_t address, uint8_t data);
uint8_t SPI_read(uint8_t address);


#endif /* MCP2515_H_ */
