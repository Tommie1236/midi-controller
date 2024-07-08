#include "button.h"

#include "pico/stdlib.h"


Button::Button(int index) : index(index) {
    this->color = {0, 0, 0};
    this->state = LedState::OFF;
}

LedState Button::getState() {
    return this->state;
};

LedState Button::setState(LedState state) {
    this->state = state;
    return this->state;
};

Color Button::setColor(Color color) {
    this->color = color;
    return this->color;
};

Color Button::getColor() {
    return this->color;
};
