#include "pico/stdlib.h"

#include "../mcp23s17/mcp23s17.h"

#ifndef MCP3008_H
#define MCP3008_H

class mcp3008 {
    private:
        const int index;
        Pin cs_pin;

    public:
        mcp3008(int indexm, Pin cs_pin);

        uint8_t read_adc(int channel);
        
};

#endif // MCP3008_H