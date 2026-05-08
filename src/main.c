#include "bsp/clock.h"
#include "bsp/gpio.h"
#include "bsp/systick.h"
#include "drivers/spi/spi_bus.h"

#define MAIN_LOOP_DELAY_MS           500U

#define MAIN_SPI_TEST_PATTERN_A      0xAAU
#define MAIN_SPI_TEST_PATTERN_B      0x55U

int main(void) {

    clock_setup();
    systick_setup();
    gpio_setup();
    spi_bus_init();

    while (1) {

        gpio_led_toggle();

        spi_bus_write_register(
                MAIN_SPI_TEST_PATTERN_A,
                MAIN_SPI_TEST_PATTERN_B
        );

        delay_ms(MAIN_LOOP_DELAY_MS);
    }

    return 0;
}
