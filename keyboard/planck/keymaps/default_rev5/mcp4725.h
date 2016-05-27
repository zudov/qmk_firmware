#ifndef MCP4725_H
#define MCP4725_H

#define I2C_ADDR        0x60

uint8_t init_mcp4725(void);

void mcp4725_send_12bits(uint16_t bits);

extern uint8_t mcp4725_status;

#endif