#include "mcp23s17.h"
#include <pin.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"


Mcp23s17::Mcp23s17(Pin& cs_pin) : cs_pin(cs_pin), pins({
    Pin(0, Parent_type::MCP23S17),           // can't find a other working solution 
    Pin(1, Parent_type::MCP23S17),
    Pin(2, Parent_type::MCP23S17),
    Pin(3, Parent_type::MCP23S17),
    Pin(4, Parent_type::MCP23S17),
    Pin(5, Parent_type::MCP23S17),
    Pin(6, Parent_type::MCP23S17),
    Pin(7, Parent_type::MCP23S17),
    Pin(8, Parent_type::MCP23S17),
    Pin(9, Parent_type::MCP23S17),
    Pin(10, Parent_type::MCP23S17),
    Pin(11, Parent_type::MCP23S17),
    Pin(12, Parent_type::MCP23S17),
    Pin(13, Parent_type::MCP23S17),
    Pin(14, Parent_type::MCP23S17),
    Pin(15, Parent_type::MCP23S17)
}) {
    for (int i = 0; i < 16; i++) {
        this->pins[i].set_parent(*this);
    };
};


Pin* Mcp23s17::get_pin(int index) {
    if (index < 0 || index > 15) {
        return nullptr;
    };
    return &this->pins[index];
};
