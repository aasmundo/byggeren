/*
 * max520.h
 *
 * Created: 04.11.2014 15:04:44
 *  Author: aasmundo
 */ 


#ifndef MAX520_H_
#define MAX520_H_

#include <stdint.h>
#include <Arduino.h>
#include "Wire.h"

void max520_init();
void max520_set_value(uint8_t value);
int16_t max520_get_position();



#endif /* MAX520_H_ */