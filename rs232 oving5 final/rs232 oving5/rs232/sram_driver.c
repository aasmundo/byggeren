#include <avr/io.h>
#include "uart.h"
#include "sram_driver.h"
#include <avr/interrupt.h>
#include <util/delay.h>

void SRAM_init(void)
{
	MCUCR |= (1<<SRE);
}

void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	unsigned int i, werrors, rerrors;
	werrors = 0;
	rerrors = 0;
	unsigned char testvalue;
	printf("Starting SRAM test...\r\n");
	//int temp = 1;
	for (i = 0; i < 0x800; i++ ) {
		testvalue = ~(i % 256);
		ext_ram[i] = testvalue;
		if (ext_ram[i] != testvalue) {
			printf("SRAM error (write phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
			werrors++;
		}
		//i = 1792;
		//i |= (1<<temp);
		//temp++;
		//printf("%x , %d \n", i,i);
	/*
	for(int k = 0; k<i; k++)
	{	
		if(ext_ram[k] != ~(k % 256))
		{
			printf("Her blir %d overskrevet av, med,: %d , %x \n", k, i, ext_ram[k]);
			//ext_ram[1792] = 0xff;
		}
	}
	*/
	}
	
	for (i = 0; i < 0x800; i++) {
		testvalue = ~(i % 256);
		if (ext_ram[i] != testvalue) {
		printf("SRAM error (read phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
		rerrors++;
		}
	}
	printf("SRAM test completed with %d errors in write phase and %d errors in read phase\r\n", werrors, rerrors);
}