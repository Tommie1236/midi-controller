#include <pin.h>

#include "pico/stdlib.h"

#ifndef MFADER_H
#define MFADER_H

class MFader {
    private:
        const int index;
        bool touched = 0;

        uint8_t updatePosition();
        void moveUp();
        void moveDown();

        Pin adc_pin;
        Pin motor_a_pin;
        Pin motor_b_pin;

    public:
        uint8_t position;

        MFader(uint index, Pin adc_pin, Pin motor_a_pin, Pin motor_b_pin);

        void moveStop();
        uint8_t getPosition();
        uint8_t moveToPosition(uint8_t newPosition);
        bool getTouched();
        bool setTouched(bool value);
};






#endif // MFADER_H
