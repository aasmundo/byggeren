#include "uart.h"

main()
{
	Enable_UAR0_Interrupt();
	unsigned word[50] = "Det funker!";
	USART0_array_transmit(word, 50);
	while(1)
	{
	
	}

}