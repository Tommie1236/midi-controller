
#include "pin/adcPin.h"

#include "mcp3008.h"
#include "hardware/adc.h"


AdcPin::AdcPin(Mcp3008* parent, uint8_t channel)
    : parent(parent), parentType(ParentType::Mcp3008), channel(channel) {

};

AdcPin::AdcPin(Rp2040* parent, uint8_t channel)
    : parent(parent), parentType(ParentType::Rp2040), channel(channel) {
        adc_init();
        adc_gpio_init(26 + this->channel);
};

uint8_t AdcPin::read() {
    switch (this->parentType) {
        case ParentType::Mcp3008:
            // TODO: implement when mcp3008's "api" is known
            // return this->parent->get_channel(this->channel)->read();
            return 0;
        case ParentType::Rp2040:
            adc_select_input(this->channel);
            return static_cast<uint8_t>(adc_read());
    }
}