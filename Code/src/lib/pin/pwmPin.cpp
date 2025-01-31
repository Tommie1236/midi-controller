
#include "pin/pwmPin.h"

//#include "pca9635.h"
#include "hardware/pwm.h"



PwmPin::PwmPin(Pca9635* parent, uint8_t pinNumber)
    : parent(parent), ParentType(ParentType::Pca9635),
    pinNumber(pinNumber) {

};

PwmPin::PwmPin(uint8_t pinNumber)
    : ParentType(ParentType::Rp2040), 
    pinNumber(pinNumber) {

        gpio_set_function(this->pinNumber, GPIO_FUNC_PWM);
        this->rp2040PwmSlice = pwm_gpio_to_slice_num(this->pinNumber);
        this->rp2040PwmChannel = pwm_gpio_to_channel(this->pinNumber);

        pwm_set_wrap(this->rp2040PwmSlice, 255); // use 8-bit PWM
        pwm_set_chan_level(this->rp2040PwmSlice, this->rp2040PwmChannel, 0);
};

uint8_t PwmPin::write(uint8_t value) {
    this->value = value;

    switch (this->ParentType) {
        case ParentType::Pca9635:
            // TODO: implement when pca9635's "api" is known
            // return this->parent->get_channel(this->channel)->write(value);
            return 0;
        case ParentType::Rp2040:
            pwm_set_chan_level(this->rp2040PwmSlice, this->rp2040PwmChannel, this->value);
            return this->value;

    }
};

bool PwmPin::enable(bool value) {
    switch (this->ParentType) {
        case ParentType::Pca9635:
            // TODO: implement when pca9635's "api" is known
            // return this->parent->get_channel(this->channel)->enable(value);
            return 0; 
        case ParentType::Rp2040:
            pwm_set_enabled(this->rp2040PwmSlice, value);
            return value;
    }
}