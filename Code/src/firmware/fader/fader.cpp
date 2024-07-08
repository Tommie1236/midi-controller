#include "fader.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

 
MFader::MFader(int index) : index(index), touched(0), position(0) {}

// TODO: change to proper adc read later
int MFader::updatePosition() {
    uint16_t value = 0/*read_adc(this->index)*/;
    return value * 0.5;
};

// TODO:
void MFader::moveUp() {
    if (!this->touched) {
        // pin x high, pin y low
    };
};

// TODO:
void MFader::moveDown() {
    if (!this->touched) {
        // pin x low, pin y high
    };
};

// TODO:
void MFader::moveStop() {
    // pin x low, pin y low
};

int MFader::getPosition() {
    this->position = this->updatePosition();
    return this->position;
};

int MFader::moveToPosition(int newPosition) {
    while (this->getPosition() != newPosition) {
        while (this->getPosition() < newPosition) {
            this->moveUp();
        };

        while (this->getPosition() > newPosition) {
            this->moveDown();
        };
    };

    this->moveStop();

    return this->position;
};
    
bool MFader::getTouched() {
    return this->touched;
};

bool MFader::setTouched(bool value) {
    this->touched = value;
    if (this->touched) {
        moveStop();
    }
    return this->touched;
};



// Define SPI pins
#define SPI_PORT spi0
#define PIN_SCK  18
#define PIN_MOSI 19
#define PIN_MISO 16
#define PIN_CS   17

// Function to initialize the SPI
void spi_init_mcp3008() {
    spi_init(SPI_PORT, 1000 * 1000);  // 5 MHz
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_init(PIN_CS);  
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
}

// Function to read a value from the MCP3008
uint16_t read_adc(uint8_t channel) {
    uint8_t buf[3];
    uint16_t result;

    buf[0] = 0x01;  // Start bit
    buf[1] = (0x08 | channel) << 4;  // Channel configuration
    buf[2] = 0x00;  // Don't care byte

    gpio_put(PIN_CS, 0);
    spi_write_read_blocking(SPI_PORT, buf, buf, 3);
    gpio_put(PIN_CS, 1);

    result = ((buf[1] & 0x03) << 8) | buf[2];  // Combine the result bytes
    return result;
};
