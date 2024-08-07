// MCP3008 10-bit ADC
// 
// Datasheet: https://ww1.microchip.com/downloads/aemDocuments/documents/MSLD/ProductDocuments/DataSheets/MCP3004-MCP3008-Data-Sheet-DS20001295.pdf

#include "mcp3008.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

#include "../mcp23s17/mcp23s17.h"
#include "../mcp23s17/pin.h"

// Define SPI pins
#define SPI_PORT spi0
#define PIN_SCK  18
#define PIN_MOSI 19
#define PIN_MISO 16
#define PIN_CS   17



void spi_init_mcp3008() {
    spi_init(SPI_PORT, 1000 * 1000);  // 5 MHz
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_init(PIN_CS);  
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
}

mcp3008::mcp3008(Pin& cs_pin) : cs_pin(cs_pin) {};

uint8_t mcp3008::read_adc_single(int channel) {
    uint8_t buf[3];

    buf[0] = 0x01;                    // spi start bit
    buf[1] = (0x8 | channel) << 4;    // or with 0x8 for single eind mode, 0x0 for differential mode
    buf[2] = 0x00;                    // dummy byte

    this->cs_pin.set(0);
    spi_write_read_blocking(spi0, buf, buf, 3);
    this->cs_pin.set(1);

    return ((buf[1] << 6) | (buf[2] >> 2)) & 0xff;      // extract only the 8 MSBits from the 10-bit ADC value
};