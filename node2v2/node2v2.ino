#include "MCP2515.h"
#include "Servo.h" 


struct MCP2515 CAN;
CANMSG melding;
CANMSG melding2;
unsigned long lang = 0; 

int pos = 0;    // variable to store the servo position 
Servo myservo;  // create servo object to control a servo 

uint8_t goal = 0;
unsigned long counter = 0;

int joy_to_pos()
{
	CAN.receiveCANMessage(&melding,1000);
	int temp = (int) melding.data[1];
	//Serial.print(temp);
	//Serial.print(", ");
	
	temp = temp * 36;

	temp = temp / 51;

	if(temp < 93 && temp > 87)
	{
		temp = 90;
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
		Serial.print(melding2.data[i]);
		Serial.println();
	}
}

void maal()
{
	if(melding.data[3] == 0)
	{
		counter++;
	}else
	{
		counter = 0;
	}
	if(counter == 25)
	{
		goal++;
		Serial.println(goal);
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
  
 myservo.attach(9);  // attaches the servo on pin 9 to the servo object 

}

void loop()
{

  if(digitalRead(19)==0)
  {
	pos = joy_to_pos();
	//Serial.println(pos);
	myservo.write(pos); 
	maal();
  }

  

  
  
}
