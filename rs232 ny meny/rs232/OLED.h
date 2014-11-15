/*
 * OLED.h
 *
 * Created: 11.09.2014 13:34:11
 *  Author: jonkol
 */ 


#ifndef OLED_H_
#define OLED_H_
#include <stdint.h>
void oled_init();
void write_c(uint8_t setting);
void oled_write(uint8_t data);
void clear_oled();
void oled_char_print(char letter);
void oled_string_print(char *streng);
void oled_set_column_address(uint8_t column_start, uint8_t column_end);
void oled_set_page_address(uint8_t page_start, uint8_t page_end);
void oled_address_reset();
void print_to_frame_buffer(uint8_t pixels, uint16_t pos);
void print_from_frame_buffer();
void oled_print_graphics(int frame);



#endif /* OLED_H_ */