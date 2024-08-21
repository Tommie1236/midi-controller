#include <stdio.h>
#include "hardware/gpio.h"
#include "pico/time.h"
#include "pico/stdlib.h"
//#include "TFT_eSPI/TFT_eSPI.h"

#include <fader.h>
#include <button.h>
// #include <encoder.h> (not yet implemented)



//#define LS30 // uncomment when using the ls30 debounc ic for the encoders (not yet inplemented)



#define FADER_1_A 10
#define FADER_1_B 11
#define FADER_2_A 12
#define FADER_2_B 13



int main () {
    const uint LED_PIN = PICO_DEFAULT_LED_PIN; 
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    spi_init_mcp3008();
    stdio_init_all(); // usb/uart stdio for printf/debug

    MFader fader_1(0);
    MFader fader_2(1);

    gpio_put(LED_PIN, 1);
    printf("online\n");

    while (1) {
        int value1 = fader_1.getPosition();
        int value2 = fader_2.getPosition();
        printf("%d %d \n", value1, value2);
        fader_1.moveToPosition(value2);
    };
    return 0;

};