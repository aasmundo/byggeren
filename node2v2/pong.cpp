/*
 * pong.cpp
 *
 * Created: 16.11.2014 13:45:02
 *  Author: aasmundo
 */ 

#include "pong.h"

unsigned long lang;

int pos;    // variable to store the servo position
Servo myservo;  // create servo object to control a servo

uint8_t state;


void pong_init()
{
	myservo.attach(9);  // attaches the servo on pin 9 to the servo object
	max520_init();
	pinMode(15, OUTPUT);
	digitalWrite(15, HIGH);
	state = IN_MENU;
}

void solenoid(int fire)
{
	
	if(fire != 0)
	{
		digitalWrite(15,LOW);
	}else
	{
		digitalWrite(15, HIGH);
	}
}

void pong_data_update()
{
	receive_data();
}

void pong_loop_this()
{
	state = get_state();
	if(state == INGAME)
	{
		myservo.write(control(SLIDER));
		motor_control(control(X));
		solenoid(control(CLICK));
		
	}else
	{
		motor_control(127);
		myservo.write(90);
		solenoid(0);
	}
	

	
		
}

int motor_control(uint8_t number)
{
	int16_t temp = number;
	//Serial.print(temp);
	if(number < 128)
	{
		digitalWrite(A6, LOW);
		temp = 127 - temp;
		temp += temp;
		
	}else
	{
		digitalWrite(A6, HIGH);
		temp = temp - 128;
		temp += temp;
	}
	max520_set_value(temp);
}

