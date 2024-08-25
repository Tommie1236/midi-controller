#include "pico/stdlib.h"
#include "hardware/spi.h"

#include <pin.h>

#ifndef MCP3008_H
#define MCP3008_H

class mcp3008 {
    private:
        spi_inst_t *spi_port;
        Pin cs_pin;
    
    public:
        mcp3008(spi_inst_t *spi_port ,Pin& cs_pin);

        uint8_t read_adc_single(int channel);
        
};



void spi_init_mcp3008();

#endif // MCP3008_H
