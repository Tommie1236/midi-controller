#include "fader.h"
#include "mcp3008.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h" //only for testing. until proper adc
#include "hardware/spi.h" //only for testing. until proper adc

#include <stdio.h>
#include <stdlib.h>

#define SPI_PORT spi0
#define PIN_SCK  18
#define PIN_MOSI 19
#define PIN_MISO 16
#define PIN_CS   17


void printBinary(uint8_t value, int bits = 8) {
    for (int i = bits-1; i >= 0; --i) { 
        printf("%d", (value >> i) & 1);
    }
}

// Function to read a value from the MCP3008
uint8_t read_adc(uint8_t channel) {
    uint8_t buf[3];
    uint8_t result;

    buf[0] = 0x01;  // Start bit
    buf[1] = (0x08 | channel) << 4;  // Channel configuration
    buf[2] = 0x00;  // Don't care byte. sends empty fills up with result

    gpio_put(PIN_CS, 0);
    spi_write_read_blocking(SPI_PORT, buf, buf, 3);
    gpio_put(PIN_CS, 1);

    result = (buf[1] & 0b00000011 << 6) | (buf[2] & 0b11111100 >> 2);  // Combine the result bytes. last 2 bits from byte 2, and first 6 bits from byte 3 combined
    
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
uint8_t MFader::updatePosition() {
    this->position = read_adc(this->index);
    return this->position;
};

// TODO: implement proper pin control
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
    // pin A low, pin B low or pin A high, pin B high

    // temp test code below
    if (this->index == 0) {
        gpio_put(10, 0);
        gpio_put(11, 0);
    } else if (this->index == 1) {
        gpio_put(12, 0);
        gpio_put(13, 0);
    }
};

uint8_t MFader::getPosition() {
    this->updatePosition();
    return this->position;
};

uint8_t MFader::moveToPosition(uint8_t newPosition) {
    
    while (this->getPosition() != newPosition) {
        
        if (abs(this->getPosition() - newPosition) < 5) {
            this->moveStop();
            break;
        };
        while (this->getPosition() < newPosition) {
            this->moveUp();
        };

        while (this->getPosition() > newPosition) {
            this->moveDown();
        };
    };

    this->moveStop();
    this->updatePosition();

    return this->position;
};
    
// implement touch detection    
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



