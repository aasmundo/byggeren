/*
 * node_com.cpp
 *
 * Created: 16.11.2014 13:51:00
 *  Author: oma
 */ 

#include "node_com.h"

struct MCP2515 CAN;
CANMSG melding;

void node_com_init()
{
	CAN.initCAN(CAN_BAUD_500K);
	CAN.setCANNormalMode(true);
	pinMode(19, INPUT);
	
}

void receive_data()
{
	CAN.receiveCANMessage(&melding,1000);
}

uint8_t get_state()
{
	return melding.data[5];
}

int control(int function) // 0 and 1 => x,y joystick,2 slider, 3, button click, 4 goal sensor
{
	int temp = (int) melding.data[function];
	if(function < 2) //x or y joystick
	{
		temp = temp * 36;

		temp = temp / 51;

		if(temp < 93 && temp > 87)
		{
			temp = 90;
		}
	}
	return temp;  
}

void CAN_data_printer()
{
	Serial.print("Data mottatt: \n");
	CAN.receiveCANMessage(&melding,1000);
	Serial.print("adresse: ");
	Serial.print(melding.adrsValue);
	Serial.println();
	Serial.print("datalengde: ");
	Serial.print(melding.dataLength);
	Serial.println();
	for(int i = 0;i < melding.dataLength; i++)
	{
		Serial.print("D");
		Serial.print(i);
		Serial.print(": ");
		Serial.print(melding.data[i]);
		Serial.println();
	}
}

void joystick_printer()
{
	CAN.receiveCANMessage(&melding,1000);
	Serial.print("y: ");
	Serial.print(melding.data[0]);
	Serial.print(", x: ");
	Serial.print(melding.data[1]);
	if(melding.data[2] == 1)
	{
		Serial.print("TRYKK!");
	}
	Serial.println();
}