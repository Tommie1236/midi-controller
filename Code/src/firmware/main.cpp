#include <stdio.h>
#include "hardware/gpio.h"
#include "pico/time.h"
#include "pico/stdlib.h"
//#include "TFT_eSPI/TFT_eSPI.h"

#include "fader/fader.h"
#include "button/button.h"

/* ------------------------------------------------------- */




/* ------------------------------------------------------- */



int main () {
    const uint LED_PIN = PICO_DEFAULT_LED_PIN; 
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    spi_init_mcp3008();
    stdio_init_all();

    MFader fader0(0);
    MFader fader1(1);

    gpio_put(LED_PIN, 1);

    uint8_t rx_buffer[3] = {0x00, 0x22, 0x36};
    printf("value %u\n", ((rx_buffer[1] << 6) | (rx_buffer[2] >> 2)) & 0xff);

    while (0) {
        int value0 = fader0.getPosition();
        int value1 = fader1.getPosition();
        printf("%d %d \n", value0, value1);
        sleep_ms(100);
    };
    return 0;

};