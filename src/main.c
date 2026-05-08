#include "bsp/clock.h"
#include "bsp/gpio.h"
#include "bsp/systick.h"
#include "bsp/spi.h"

#define MAIN_LOOP_DELAY_MS           500U

#define MAIN_SPI_TEST_PATTERN_A      0xAAU
#define MAIN_SPI_TEST_PATTERN_B      0x55U

int main(void) {

    clock_setup();
    systick_setup();
    gpio_setup();
    spi_setup();

    while (1) {

        gpio_led_toggle();

        spi_cs_select();
        spi_transfer_byte(MAIN_SPI_TEST_PATTERN_A);
        spi_transfer_byte(MAIN_SPI_TEST_PATTERN_B);
        spi_cs_deselect();

        delay_ms(MAIN_LOOP_DELAY_MS);
    }

    return 0;
}
