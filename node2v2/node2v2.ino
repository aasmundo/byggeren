#include "MCP2515.h"


struct MCP2515 CAN;
CANMSG melding;
CANMSG melding2;
 
void setup()
{

  Serial.begin(9600);
  CAN.initCAN(CAN_BAUD_100K);
  CAN.setCANNormalMode(true);


  melding.isExtendedAdrs = false;
  melding.adrsValue = 101;
  melding.dataLength = 8;
  melding.rtr = false;

  melding2.data[0] = 5;
  Serial.print("mottar: ");
  for(int i = 0;i<8;i++)
  {
	melding.data[i] = 7 - i;
  }
  //CAN.transmitCANMessage(melding, 1000);
}

void loop()
{
  CAN.transmitCANMessage(melding, 1000);
  Serial.print("mottar:    ");
  CAN.receiveCANMessage(&melding2,1000);
  Serial.print(melding2.data[0]);
  

}
