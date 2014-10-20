#include "MCP2515.h"


struct MCP2515 CAN;
CANMSG melding;
CANMSG melding2;
 
void setup()
{

  Serial.begin(9600);
  CAN.initCAN(CAN_BAUD_100K);
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
  CAN.transmitCANMessage(melding, 1000);
}

void loop()
{
  if(digitalRead(19)==0)
  {
    Serial.print("Data mottatt: \n");
    CAN.receiveCANMessage(&melding2,1000);
	Serial.print("adresse: ");
	Serial.print(melding2.adrsValue);
	Serial.println();
	Serial.print("datalengde: ");
	Serial.print(melding2.dataLength);
	Serial.println();
	for(int i = 0;i < melding2.dataLength; i++)
	{
		Serial.print("D");
		Serial.print(i);
		Serial.print(": ");
		Serial.print(melding2.data[i]);
		Serial.println();
	}
  }
  CAN.transmitCANMessage(melding, 1000);

}
