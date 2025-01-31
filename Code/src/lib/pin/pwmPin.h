
#ifndef PwmPin_H
#define PwmPin_H

#include <variant>
#include <pico/stdlib.h>

class Pca9635;

enum class ParentType {
    Pca9635,
    Rp2040
};

class PwmPin {
    private:
        const ParentType ParentType;
        const Pca9635* parent = nullptr;
        const uint8_t pinNumber;
        uint8_t rp2040PwmSlice;
        bool rp2040PwmChannel;
        
        uint8_t value;
        bool enabled;
    
    public:
        PwmPin(Pca9635 *parent, uint8_t pinNumber);
        PwmPin(uint8_t pinNumber); // assumes parent is rp2040

        uint8_t write(uint8_t value);
        bool enable(bool value);
};




#endif // PwmPin_H
