
#ifndef AdcPin_H
#define AdcPin_H

#include <variant>
#include <pico/stdlib.h>

class Mcp3008;
class Rp2040;

enum class ParentType {
    Mcp3008,
    Rp2040
};

using ParentVariant = std::variant<
    Mcp3008*,
    Rp2040*
>;

class AdcPin {
    private:
        const ParentType parentType;
        const ParentVariant parent;
        const uint8_t channel;
    
    public:
        AdcPin(Mcp3008 *parent, uint8_t channel);
        AdcPin(Rp2040 *parent, uint8_t channel);

        uint8_t read();
};

#endif // AdcPin_h