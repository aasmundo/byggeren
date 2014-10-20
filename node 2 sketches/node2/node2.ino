// demo: CAN-BUS Shield, send data
#include "mcp_can.h"
#include "SPI.h"
long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];


MCP_CAN CAN0(53);                                      // Set CS to pin 53
void send()
{
	unsigned char stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};	
	// send data:  id = 0x00, standard flame, data len = 8, stmp: data buf
  CAN0.sendMsgBuf(0x00, 0, 8, stmp);
}


void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(19, INPUT); 
  // init can bus, baud rate: 50k
  if(CAN0.begin(CAN_50KBPS) == CAN_OK) Serial.print("can init ok!!\r\n");
  else Serial.print("Can init fail!!\r\n");

  //SPI.begin();
  send();
}
byte tall = 0xf0;  
void loop()
{
  
   if(!digitalRead(19))                         // If pin 2 is low, read receive buffer
    {
      CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
      rxId = CAN0.getCanId();                    // Get message ID
      Serial.print("ID: ");
      Serial.print(rxId, HEX);
      Serial.print("  Data: ");
      for(int i = 0; i<len; i++)                // Print each byte of the data
      {
        if(rxBuf[i] < 0x10)                     // If data byte is less than 0x10, add a leading zero
        {
          Serial.print("0");
        }
        Serial.print(rxBuf[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
	  send();
    }                       // send data per 100ms
	delay(100);
	digitalWrite(53, LOW);
	SPI.transfer(0x03);
	SPI.transfer(0x2d);
	tall = SPI.transfer(0x00);
	digitalWrite(53, HIGH);
	//Serial.print(tall);
  
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

