#include "mcp4921.h"

void setupSPI(uint8_t mode, uint8_t dord, uint8_t interrupt, uint8_t clk) {
  if (clk == SPI_SLAVE) {
    SPI_DDR &= ~(1<<SPI_MOSI_PIN); //INPUT
    SPI_DDR |= (1<<SPI_MISO_PIN);  // OUTPUT
    SPI_DDR &= (1<<SPI_SS_PIN);    // INPUT
    SPI_DDR &= ~(1<<SPI_SCK_PIN);  // INPUT
  } else {
    SPI_DDR |= (1<<SPI_MOSI_PIN);  // OUTPUT
    SPI_DDR &= ~(1<<SPI_MISO_PIN); // INPUT
    SPI_DDR |= (1<<SPI_SCK_PIN);   // OUTPUT
    SPI_DDR |= (1<<SPI_SS_PIN);    // OUTPUT
  }
  
  // Configure SPCR (SPI Control Register)
  SPCR = 0; // Clear SPCR
  SPCR = ((interrupt ? 1 : 0) << SPIE) // Interrupt Enable
       | (1<<SPE) // Enable SPI bus
       | (dord<<DORD) // LSB or MSB
       | (((clk != SPI_SLAVE) ? 1 : 0) << MSTR)  // Slave or Master
       | (((mode & 0x02) == 0x02) << CPOL) // Clock timing mode CPHA.
       | (((mode & 0x01) == 0x01) << CPHA) // Clock timing mode CPHA.
       | (((clk & 0x02) == 2) << SPR1) // CPU clock divisor SPR1
       | (((clk & 0x01) << SPR0)); // cpu clock divisor SPRO
  SPSR = (((clk & 0x04) == 4) << SPI2X);
}

void disableSPI() {
  SPCR &= ~(1<<SPE);
}

uint8_t sendSPI(uint8_t data) {
  SPDR = data;
  
  while (!(SPSR & (1<<SPIF)));
  
  return SPDR;
}

uint8_t received_from_spi(uint8_t data)
{
  SPDR = data;
  return SPDR;
}

void writeMCP492x(uint16_t data, uint8_t config) {
  // Take the top 4 bits of config and the top 4 valid bits (data is actually a 12 bit number) and or them together
  uint8_t top_msg = (config & 0xF0) | (0x0F & (data >> 8));
  
  // Take the bottom octet of data
  uint8_t lower_msg = (data & 0x00FF);
   
  // Select our DAC
  SELECT_DAC;
  // Send first 8 bits
  sendSPI(top_msg);
  // Send second 8 bits
  sendSPI(lower_msg);
  DESELECT_DAC;
}