#include "i2cmaster.h"
#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>

bool i2c_initialized = 0;
uint8_t mcp4725_status = 0x20;

uint8_t init_mcp4725(void) {
    mcp4725_status = 0x0;

    // I2C subsystem
    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized++;
        _delay_ms(100);
    }

    return mcp4725_status;
}

void mcp4725_send_12bits(uint16_t bits) {
    bits = bits & 0xFFF;

    if (mcp4725_status) {
      mcp4725_status = 0;
    }
    mcp4725_status = i2c_start(0b11000000); 
    mcp4725_status = i2c_write(0b01100000); 
    mcp4725_status = i2c_write(bits / 16); 
    mcp4725_status = i2c_write((bits % 16) << 4);

    // fast mode?
    // mcp4725_status = i2c_start(0b11000000);       
    // mcp4725_status = i2c_write((bits >> 8) & 0xF); 
    // mcp4725_status = i2c_write((bits & 0xF));     
    i2c_stop();
}