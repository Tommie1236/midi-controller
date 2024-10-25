
#ifndef ENCODER_H
#define ENCODER_H


#include "pico/stdlib.h"
#include <pin.h>
#include <functional>


const int NUM_ENCODERS = 10;
extern bool LED_BUFFER[NUM_ENCODERS * 17];



class Encoder {

    private:
        const int index;

        Pin& pin_a;
        Pin& pin_b;
        Pin& pin_switch;

        bool pushed = 0;

        std::function<void(int, bool)> callbackRotate;
        std::function<void(int)> callbackPush;
        
        // for absolute mode.
        int maxValue = 0;
        int Value = 0;

    public:

        Encoder(int index, Pin& pin_a, Pin& pin_b, Pin& pin_switch,
                std::function<void(int, bool)> callbackRotate,
                std::function<void(int)> callbackPush);


        bool set_led(int led_num, bool value);
        bool get_led(int led_num);
        bool set_led_range(int start, int end, bool value);
};

#endif // ENCODER_H