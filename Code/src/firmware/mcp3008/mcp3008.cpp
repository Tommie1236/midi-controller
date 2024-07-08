// MCP3008 10-bit ADC
// 
// Datasheet: https://ww1.microchip.com/downloads/aemDocuments/documents/MSLD/ProductDocuments/DataSheets/MCP3004-MCP3008-Data-Sheet-DS20001295.pdf

#include "mcp3008.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

#include "../mcp23s17/mcp23s17.h"

mcp3008::mcp3008(int index, Pin cs_pin) : index(index), cs_pin(cs_pin) {};

uint8_t mcp3008::read_adc(int channel) {
    uint8_t tx_buffer[3];
    uint8_t rx_buffer[3];

    tx_buffer[0] = 0x01;                    // spi start bit
    tx_buffer[1] = (0x8 | channel) << 4;    // or with 0x8 for single eind mode, 0x0 for differential mode
    tx_buffer[2] = 0x00;                    // dummy byte

    this->cs_pin.set(0);
    spi_write_read_blocking(spi0, tx_buffer, rx_buffer, 3);
    this->cs_pin.set(1);

    return ((rx_buffer[1] << 6) | (rx_buffer[2] >> 2)) & 0xff;      // extract only the 8 MSBits from the 10-bit ADC value
};