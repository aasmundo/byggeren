#include "MCP2515.h"


struct MCP2515 CAN;
CANMSG melding;
CANMSG melding2;
unsigned long lang = 0; 


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
		Serial.print(melding2.data[i]);
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
void setup()
{

  Serial.begin(115200);
  CAN.initCAN(CAN_BAUD_500K);
  CAN.setCANNormalMode(true);
  pinMode(19, INPUT);

  melding.isExtendedAdrs = false;
  melding.adrsValue = 101;
  melding.dataLength = 8;
  melding.rtr = false;

  melding2.data[0] = 5;
  for(int i = 0;i<8;i++)
  {
	melding.data[i] = 7 - i;
  }
}

void loop()
{
  if(digitalRead(19)==0)
  {
    joystick_printer();
  }
  
}
