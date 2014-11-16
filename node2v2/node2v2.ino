#include "pong.h"
#include "node_com.h"














void setup()
{

  Serial.begin(115200);
  pong_init();
  node_com_init();
  
 
}

void loop()
{

  if(digitalRead(19)==0)
  {
	receive_data();	
  }
	
  pong_loop_this();
  CAN_data_printer();

  
  
}
