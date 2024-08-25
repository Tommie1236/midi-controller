// tlc59282 test

#include <stdio.h>
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "pico/time.h"
#include "pico/stdlib.h"


#define spi_port spi0
#define TX_PIN 19
#define CLK_PIN 18
#define LATCH_PIN 20
#define BLANK_PIN 21


void pulse(int pin) {
    gpio_put(pin, 1);
    sleep_ms(1);
    gpio_put(pin, 0);
}

void set_led_pattern(uint8_t *pattern, size_t len) {
    gpio_put(LATCH_PIN, 0);
    gpio_put(BLANK_PIN, 1); // Turn off all LEDs

    spi_write_blocking(spi_port, pattern, len);

    gpio_put(LATCH_PIN, 1);
    gpio_put(LATCH_PIN, 0);
    gpio_put(BLANK_PIN, 0); // Enable LED drivers
}

void demo_static_pattern() {
    uint8_t buf[2] = {0b10101010, 0b01010101}; // Example static pattern with alternating LEDs
    set_led_pattern(buf, sizeof(buf));
}

void demo_moving_light() {
    uint8_t buf[2];
    for (int i = 0; i < 8; i++) {
        buf[0] = 1 << i; // Move one bit in the first byte
        buf[1] = 0;      // Second byte is off
        set_led_pattern(buf, sizeof(buf));
        sleep_ms(100);
    }
}

void demo_chase_pattern() {
    uint8_t buf[2];
    for (int i = 0; i < 16; i++) {
        buf[0] = 1 << i; // Chase pattern in the first byte
        buf[1] = 0;      // Second byte is off
        set_led_pattern(buf, sizeof(buf));
        sleep_ms(100);
    }
    for (int i = 14; i >= 0; i--) { // Chase backwards
        buf[0] = 1 << i;
        buf[1] = 0;
        set_led_pattern(buf, sizeof(buf));
        sleep_ms(100);
    }
}

void demo_blinking_pattern() {
    uint8_t buf[2] = {0b11111111, 0b11111111}; // All LEDs on
    set_led_pattern(buf, sizeof(buf));
    sleep_ms(500);
    buf[0] = 0;
    buf[1] = 0; // All LEDs off
    set_led_pattern(buf, sizeof(buf));
    sleep_ms(500);
}

int main() {

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    gpio_init(LATCH_PIN);
    gpio_init(BLANK_PIN);
    //gpio_init(TX_PIN);
    //gpio_init(CLK_PIN);
    gpio_set_dir(LATCH_PIN, GPIO_OUT);
    gpio_set_dir(BLANK_PIN, GPIO_OUT);
    //gpio_set_dir(TX_PIN, GPIO_OUT);
    //gpio_set_dir(CLK_PIN, GPIO_OUT);



    // bool tx = 0;

    // while (true) {
    //     tx = ! tx;
    //     gpio_put(TX_PIN, tx);
    //     pulse(CLK_PIN);
    //     pulse(LATCH_PIN);
    //     sleep_ms(300);
    // }

    
    gpio_set_function(CLK_PIN, GPIO_FUNC_SPI);
    spi_init(spi_port, 1000000);
    gpio_set_function(TX_PIN, GPIO_FUNC_SPI);

    gpio_put(LATCH_PIN, 0);
    gpio_put(BLANK_PIN, 1); // turn off all leds

    uint8_t buf[2];

    buf[0] = 0b01110111;
    buf[1] = 0b11011101;



    spi_write_blocking(spi_port, buf, 2);
    gpio_put(LATCH_PIN, 1);
    gpio_put(LATCH_PIN, 0);

    gpio_put(BLANK_PIN, 0); //enalble led drivers




    while (true) {
        demo_static_pattern();
        sleep_ms(1000);

        demo_moving_light();
        sleep_ms(1000);

        demo_chase_pattern();
        sleep_ms(1000);

        demo_blinking_pattern();
        sleep_ms(1000);
    }

    return 0;
}