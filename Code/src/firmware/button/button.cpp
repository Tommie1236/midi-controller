#include "button.h"

#include "pico/stdlib.h"


Button::Button(int index) : index(index) {
    this->color = {0, 0, 0};
    this->state = LedState::OFF;
}

LedState Button::get_state() {
    return this->state;
};

LedState Button::set_state(LedState state) {
    this->state = state;
    return this->state;
};

Color Button::set_color(Color color) {
    this->color = color;
    return this->color;
};

Color Button::get_color() {
    return this->color;
};
