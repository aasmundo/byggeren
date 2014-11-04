/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Mega 2560 or Mega ADK, Platform=avr, Package=arduino
*/

#define __AVR_ATmega2560__
#define ARDUINO 101
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define __cplusplus
extern "C" void __cxa_pure_virtual() {;}

int motor_control(uint8_t number);
int joy_to_pos();
void CAN_data_printer();
void maal();
void joystick_printer();
//
//

#include "C:\Program Files\Arduino\hardware\arduino\variants\mega\pins_arduino.h" 
#include "C:\Program Files\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Users\aasmundo\Documents\byggeren\node2v2\node2v2.ino"
#include "C:\Users\aasmundo\Documents\byggeren\node2v2\MCP2515.cpp"
#include "C:\Users\aasmundo\Documents\byggeren\node2v2\MCP2515.h"
#include "C:\Users\aasmundo\Documents\byggeren\node2v2\SPI.cpp"
#include "C:\Users\aasmundo\Documents\byggeren\node2v2\SPI.h"
#include "C:\Users\aasmundo\Documents\byggeren\node2v2\Servo.cpp"
#include "C:\Users\aasmundo\Documents\byggeren\node2v2\Servo.h"
#include "C:\Users\aasmundo\Documents\byggeren\node2v2\Wire.cpp"
#include "C:\Users\aasmundo\Documents\byggeren\node2v2\Wire.h"
#include "C:\Users\aasmundo\Documents\byggeren\node2v2\max520.cpp"
#include "C:\Users\aasmundo\Documents\byggeren\node2v2\max520.h"
#include "C:\Users\aasmundo\Documents\byggeren\node2v2\twi.c"
#include "C:\Users\aasmundo\Documents\byggeren\node2v2\twi.h"
