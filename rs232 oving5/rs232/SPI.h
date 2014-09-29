/*
 * SPI.h
 *
 * Created: 18.09.2014 17:29:26
 *  Author: jonkol
 */ 


#ifndef SPI_H_
#define SPI_H_
#include <stdint.h>


void SPI_master_init();
void SPI_transmit(uint8_t data);
void SPI_CS_low();
void SPI_CS_high();
uint8_t SPI_data(uint8_t data);

#endif /* SPI_H_ */