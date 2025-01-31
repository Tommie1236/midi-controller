
#ifndef AdcPin_H
#define AdcPin_H

#include <variant>
#include <pico/stdlib.h>

class Mcp3008;

enum class ParentType {
    Mcp3008,
    Rp2040
};

class AdcPin {
    private:
        const ParentType parentType;
        const Mcp3008* parent = nullptr;
        const uint8_t channel;
    
    public:
        AdcPin(Mcp3008 *parent, uint8_t channel);
        AdcPin(uint8_t channel); // assumes parent is rp2040

        uint8_t read();
};

#endif // AdcPin_h