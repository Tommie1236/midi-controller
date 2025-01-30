// Deprecated
#include "pin.h"

#include <mcp23s17.h>
#include <mcp3008.h>
//#include <pca9635.h>
//#include <mtch105.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"

// for rp2040 index is gpio number
// for mcp23s17 index is pin number
Pin::Pin(int index,
         Parent_type parent_type,
         Mcp23s17 *parent)
         : index(index),
           parent_type(parent_type) {
      
};

bool Pin::set(bool value) {
    
    switch (this->parent_type) {
        case Parent_type::MCP23S17:
            
            break;
        
        case Parent_type::RP2040:
            gpio_put(this->index, value);
            break;
        
        case Parent_type::MCP3008:
            
            break;
        
        case Parent_type::PCA9635:
            
            break;
        
        case Parent_type::MTCH105:
            // nothing. cant write to mtch105 pins
            break;

        default:
            break;
    };
    this->get();
    return this->value;
};

bool Pin::get() {
    switch (this->parent_type) {
        case Parent_type::MCP23S17:
        
            break;

        case Parent_type::RP2040:
            this->value = gpio_get(this->index);
            break;

        case Parent_type::MCP3008:
            
            break;
        
        case Parent_type::PCA9635:
        
            break;

        case Parent_type::MTCH105:

            break;
        
        default:
            break;
    };
    return this->value;
};

bool Pin::set_default_value(bool value) {
    this->default_value = value;
    return this->default_value;
};

Interrupt_mode Pin::get_interrupt_mode() {
    return this->interrupt_mode;
};

Interrupt_mode Pin::set_interrupt_mode(Interrupt_mode interrupt_mode) {
    this->interrupt_mode = interrupt_mode;
    // TODO: implement interrupt mode
    return this->interrupt_mode;
};