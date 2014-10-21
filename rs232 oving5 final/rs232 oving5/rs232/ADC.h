#ifndef ADC
#define ADC

void ADC_init();
ISR(INT0_vect);
unsigned char ADC_last_value(int chan);
void ADC_read(int chan);
void ADC_set_busy_state(uint8_t state);
uint8_t ADC_busy();
uint8_t ADC_last_read_input();
#endif