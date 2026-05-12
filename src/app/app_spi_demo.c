#include "app/app_spi_demo.h"

#include "bsp/gpio.h"
#include "bsp/systick.h"
#include "drivers/max7219/max7219.h"

#define APP_SPI_DEMO_PATTERN_DELAY_MS      1000U

void app_spi_demo_run(void) {

    gpio_led_toggle();

    max7219_all_on();
    delay_ms(APP_SPI_DEMO_PATTERN_DELAY_MS);

    max7219_clear();
    delay_ms(APP_SPI_DEMO_PATTERN_DELAY_MS);

    max7219_checkerboard();
    delay_ms(APP_SPI_DEMO_PATTERN_DELAY_MS);

    max7219_clear();
    delay_ms(APP_SPI_DEMO_PATTERN_DELAY_MS);
}
