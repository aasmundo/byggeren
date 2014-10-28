/*
 * Servo.h
 *
 * Created: 28.10.2014 12:07:28
 *  Author: jonkol
 */ 


#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>
#include <Arduino.h>

void PWM_setup(uint8_t pwm_period);
void PWM(uint16_t duty_cycle);





#endif /* SERVO_H_ */