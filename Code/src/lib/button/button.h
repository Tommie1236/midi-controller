
#include "pico/stdlib.h"

#include <pin.h>

#ifndef BUTTON_H
#define BUTTON_H

struct Color {
    uint8_t r, g, b;
};


enum class LedState {
    OFF,
    ON,
    BLINK,
    BREATHING
};

class Button {
    private:
        const int index;

    public:
        Color color;
        LedState state;
        

        Button(int index);


        LedState get_state();
        LedState set_state(LedState state);

        Color set_color(Color color);
        Color get_color();
        
};

#endif // BUTTON_H
