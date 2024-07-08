
#include "pico/stdlib.h"

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


        LedState getState();
        LedState setState(LedState state);

        Color setColor(Color collor);
        Color getColor();
        
};

#endif // BUTTON_H