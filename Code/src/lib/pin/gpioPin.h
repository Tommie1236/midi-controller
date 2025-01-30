
#ifndef GpioPin_H
#define GpioPin_H

#include <variant>
#include <pico/stdlib.h>

class Mcp23s17;
class Rp2040;

enum class ParentType {
    Mcp23s17,
    Rp2040
};

using ParentVariant = std::variant<
    Mcp23s17*,
    Rp2040*
>;


class GpioPin {
    private:
        const ParentType parentType;
        const ParentVariant parent;
        const uint8_t pinNumber;
    
    public:
        GpioPin(Mcp23s17 *parent, uint8_t pinNumber);
        GpioPin(Rp2040 *parent, uint8_t pinNumber);

        bool write(bool value);
        bool read();
};

#endif // GpioPin_H
