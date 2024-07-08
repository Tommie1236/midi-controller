#include "mcp23s17.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"




bool Pin::set(bool value) {
    // set the pin to the given value
    return value;
};