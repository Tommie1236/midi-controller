#include "fader.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

#include <stdio.h>

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

    result = ((((buf[1] & 0b00000011) << 6) | (buf[2] >> 2)));  // Combine the result bytes
    return result;
};
 


MFader::MFader(int index) : index(index), touched(0), position(0) {
    //temp testing code
    if (this->index == 0) {
        gpio_init(10);
        gpio_init(11);
        gpio_set_dir(10, GPIO_OUT);
        gpio_set_dir(11, GPIO_OUT);
    } else if (this->index == 1) {
        gpio_init(12);
        gpio_init(13);
        gpio_set_dir(12, GPIO_OUT);
        gpio_set_dir(13, GPIO_OUT);
    }
}

// TODO: change to proper adc read later
int MFader::updatePosition() {
    uint16_t value = read_adc(this->index);
    return value * 0.5;
};

// TODO:
void MFader::moveUp() {
    if (!this->touched) {
        // pin A high, pin B low
        // temp testing code below
        if (this->index == 0) {
            gpio_put(10, 1);
            gpio_put(11, 0);
        } else if (this->index == 1) {
            gpio_put(12, 1);
            gpio_put(13, 0);
        }
    };
};

// TODO:
void MFader::moveDown() {
    if (!this->touched) {
        // pin A low, pin B high
        // temp testing code below
        if (this->index == 0) {
            gpio_put(10, 0);
            gpio_put(11, 1);
        } else if (this->index == 1) {
            gpio_put(12, 0);
            gpio_put(13, 1);
        }
    };
};

// TODO:
void MFader::moveStop() {
    // pin A low, pin B low
    // temp test code below
    if (this->index == 0) {
        gpio_put(10, 0);
        gpio_put(11, 0);
    } else if (this->index == 1) {
        gpio_put(12, 0);
        gpio_put(13, 0);
    }
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



