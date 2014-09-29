#ifndef UART
#define UART

//#define FOSC 614400// Clock Speed
#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD - 1//FOSC/16/BAUD-1

#define set_bit(reg,bit) (reg |=(1<<bit))
#define clear_bit(reg,bit) (reg &=~(1<<bit))
#define test_bit(reg, bit) (reg & (1<<bit))


void USART_Init(unsigned int ubrr );


unsigned char USART0_Receive();

void Enable_UAR0_Interrupt();

void USART0_Transmit( unsigned char chardata );

void USART0_array_transmit( unsigned char* chardata, unsigned int array_length);



ISR(USART0_RXC_vect);

 #endif /* UART */