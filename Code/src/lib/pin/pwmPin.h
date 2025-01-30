
#ifndef PwmPin_H
#define PwmPin_H

#include <variant>
#include <pico/stdlib.h>

class Pca9635;
class Rp2040;

enum class ParentType {
    Pca9635,
    Rp2040
};

using ParentVariant = std::variant<
    Pca9635*,
    Rp2040*
>;

class PwmPin {
    private:
        const ParentType ParentType;
        const ParentVariant parent;
        const uint8_t pinNumber;
        uint8_t rp2040PwmSlice;
        bool rp2040PwmChannel;
        
        uint8_t value;
        bool enabled;
    
    public:
        PwmPin(Pca9635 *parent, uint8_t pinNumber);
        PwmPin(Rp2040 *parent, uint8_t pinNumber);

        uint8_t write(uint8_t value);
        bool enable(bool value);
};




#endif // PwmPin_H
