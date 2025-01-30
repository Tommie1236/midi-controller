#include "pin/gpioPin.h"

#include "mcp23s17.h"        
#include "hardware/gpio.h"  



GpioPin::GpioPin(Mcp23s17* parent, uint8_t pinNumber)
    : parent(parent), parentType(ParentType::Mcp23s17), pinNumber(pinNumber) {

};

GpioPin::GpioPin(Rp2040* parent, uint8_t pinNumber)
    : parent(parent), parentType(ParentType::Rp2040), pinNumber(pinNumber) {

};


bool GpioPin::read() {
    switch (this->parentType) {
        case ParentType::Mcp23s17:
            // TODO: implement when mcp23s17's "api" is known
            // return this->parent->get_pin(this->pinNumber)->get();
            return false;
        case ParentType::Rp2040:
            return gpio_get(this->pinNumber);
    }
}

bool GpioPin::write(bool value) {
    switch (this->parentType) {
        case ParentType::Mcp23s17:
            // TODO: implement when mcp23s17's "api" is known
            // return this->parent->get_pin(this->pinNumber)->set(value);
            return 0;
        case ParentType::Rp2040:
            gpio_put(this->pinNumber, value);
            return value;
    }
}