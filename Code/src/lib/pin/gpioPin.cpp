#include "pin/gpioPin.h"

#include "mcp23s17.h"        
#include "hardware/gpio.h"  



GpioPin::GpioPin(Mcp23s17* parent, uint8_t pinNumber, PinMode direction = PinMode::INPUT)
    : parent(parent), parentType(ParentType::Mcp23s17), pinNumber(pinNumber) {
        this->set_direction(direction);
};

GpioPin::GpioPin(uint8_t pinNumber, PinMode direction = PinMode::INPUT)
    : parentType(ParentType::Rp2040), pinNumber(pinNumber) {
        this->set_direction(direction);
};


bool GpioPin::read() {
    switch (this->parentType) {
        case ParentType::Mcp23s17:
            // TODO: implement when mcp23s17's "api" is known
            // return this->parent->get_pin(this->pinNumber)->get();
            break;
        case ParentType::Rp2040:
            this->value = gpio_get(this->pinNumber);
            break;
    }
    return this->value;
}

bool GpioPin::write(bool value) {
    this->value = value;

    switch (this->parentType) {
        case ParentType::Mcp23s17:
            // TODO: implement when mcp23s17's "api" is known
            // return this->parent->get_pin(this->pinNumber)->set(value);
            break;
        case ParentType::Rp2040:
            gpio_put(this->pinNumber, this->value);
            break;
    }
    return this->value;
}

bool GpioPin::set_default_value(bool value) {
    this->defaultValue = value;

    if (this->parentType == ParentType::Mcp23s17) {
        // TODO: implement when mcp23s17's "api" is known
    } // rp2040 doesn't need/have a default gpio value like the mcp23s17
};

PinMode GpioPin::set_direction(PinMode direction) {
    this->direction = direction;
    switch (this->parentType) {
        case ParentType::Mcp23s17:
            break;
        case ParentType::Rp2040:
            gpio_set_dir(this->pinNumber, static_cast<bool>(this->direction));
            break;
    }
    return this->direction;
};