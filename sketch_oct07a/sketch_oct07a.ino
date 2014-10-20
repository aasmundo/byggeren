

#include "MCP2515.h"




int led = 13;
const uint8_t chip_select_pin = 53;



void setup() {                

  pinMode(led, OUTPUT); 
  Serial.begin(9600);
  
  attachInterrupt(4,CAN_interrupt,FALLING);
  
}


void loop() {
  
}

void CAN_interrupt()
{
  Serial.print("Gunnar er homo \n"); 
}
