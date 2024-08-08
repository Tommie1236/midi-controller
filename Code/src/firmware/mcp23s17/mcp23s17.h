
#ifndef MCP23S17_H
#define MCP23S17_H

#include <array>
#include <pin.h>



class Mcp23s17 {
    private:
        Pin& cs_pin;
        std::array<Pin, 16> pins;
        bool interrupt_enabled = true;
        bool interrupt_ORed = false;

    public:
        Mcp23s17(Pin& cs_pin);


        Pin *get_pin(int index);
};


#endif // MCP23S17_H