
// TODO: interrupts
#ifndef GpioPin_H
#define GpioPin_H

#include <variant>
#include <pico/stdlib.h>

class Mcp23s17;

enum class ParentType {
    Mcp23s17,
    Rp2040
};

enum class PinMode {
    INPUT   = 0,
    OUTPUT  = 1
};


class GpioPin {
    private:
        const ParentType parentType;
        Mcp23s17* const parent = nullptr;
        const uint8_t pinNumber;

        bool value = 0;
        bool defaultValue = 0; // mcp23s17 only
        PinMode direction = PinMode::INPUT;
    
    public:
        GpioPin(Mcp23s17 *parent, uint8_t pinNumber, PinMode direction);
        GpioPin(uint8_t pinNumber, PinMode direction);  // assumes parent is rp2040

        bool write(bool value);
        bool read();

        PinMode set_direction(PinMode direction);
        bool set_default_value(bool value);

};

#endif // GpioPin_H
