
const uint8_t chip_select_pin = 53;

void SPI_init()
{
  SPI.begin();
  attachInterrupt(4,CAN_interrupt,FALLING);
    
}

void SPI_CS_high()
{
   digitalWrite(chip_select_pin, HIGH); 
}

void SPI_CS_low()
{
   digitalWrite(chip_select_pin, LOW); 
}

void SPI_write(uint8_t address, uint8_t data)
{
  SPI_CS_low(); 
  SPI.transfer(0b00000010);
  SPI.transfer(address);
  SPI.transfer(data);
  SPI_CS_high();
}

uint8_t SPI_read(uint8_t address)
{
  uint8_t result;
  SPI_CS_low(); 
  SPI.transfer(0b00000011);
  SPI.transfer(address);
  result = SPI.transfer(0x00);
  SPI_CS_high();
  return result;
}


