#include "encoder.h"
#include <pin.h>
#include <stdexcept>

#include "pico/stdlib.h"




bool LED_BUFFER[NUM_ENCODERS * 17] = {0};

Encoder::Encoder(int index, Pin& pin_a, Pin& pin_b, Pin& pin_switch,
                 std::function<void(int, bool)> callbackRotate = nullptr,
                 std::function<void(int)> callbackPush = nullptr)
                 : index(index), pin_a(pin_a), pin_b(pin_b), pin_switch(pin_switch),
                 callbackRotate(callbackRotate), callbackPush(callbackPush) {}


bool Encoder::set_led(int led_num, bool value) {
 
    if (led_num < 0 || led_num > 16 ) return false;

    // led 16 is the dot below and is driven by one tlc59282 at the end for all the encoder dots. Because the driver has only 16 outputs. 
    if (led_num == 16) {
        LED_BUFFER[NUM_ENCODERS * 16 + index] = value;
        return true;
    }

    LED_BUFFER[index * 16 + led_num] = value;
    return true;
}

bool Encoder::get_led(int led_num) {
    if (led_num < 0 || led_num > 16) throw std::out_of_range("led_num must be in range 0-16");
    
    if (led_num == 16) {
        return LED_BUFFER[NUM_ENCODERS * 16 + index];
    }
    
    return LED_BUFFER[index * 16 + led_num];
}

bool Encoder::set_led_range(int start, int end, bool value) {

    if (start < 0 || start > 15 ||
        end < 1 || end > 16 ||
        start > end) return false;

    for (int led = start; led <= end; led++) {
        if (led == 16) {
            LED_BUFFER[NUM_ENCODERS * 16 + index] = value;
            continue;
        }
        LED_BUFFER[index * 16 + led] = value;
    }

    return true;
}