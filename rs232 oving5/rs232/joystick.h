/*
 * joystick.h
 *
 * Created: 09.09.2014 13:16:42
 *  Author: gr5
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

void x_pos();
void y_pos();
uint8_t joy_smoothing(uint8_t input);
uint8_t unresolved_button_press();
ISR(INT1_vect);
void joy_button_init();



#endif /* JOYSTICK_H_ */