#include "pico/stdlib.h"

#include "../mcp23s17/mcp23s17.h"
#include "../mcp23s17/pin.h"

#ifndef MCP3008_H
#define MCP3008_H

class mcp3008 {
    private:
        Pin cs_pin;
    
    public:
        mcp3008(Pin& cs_pin);

        uint8_t read_adc_single(int channel);
        
};

#endif // MCP3008_H