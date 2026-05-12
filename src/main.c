#include "bsp/clock.h"
#include "bsp/gpio.h"
#include "bsp/systick.h"
#include "drivers/spi/spi_bus.h"
#include "drivers/max7219/max7219.h"

#define MAIN_LOOP_DELAY_MS           500U

#define MAIN_SPI_TEST_PATTERN_A      0xAAU
#define MAIN_SPI_TEST_PATTERN_B      0x55U

int main(void) {

    clock_setup();
    systick_setup();
    gpio_setup();

    spi_bus_init();
    max7219_init();

    while (1) {

        gpio_led_toggle();

        delay_ms(MAIN_LOOP_DELAY_MS);
    }

    return 0;
}
