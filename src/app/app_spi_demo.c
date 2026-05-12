#include "app/app_spi_demo.h"

#include "bsp/gpio.h"
#include "bsp/systick.h"
#include "drivers/max7219/max7219.h"

#define APP_SPI_DEMO_PATTERN_DELAY_MS      1000U

static const uint8_t smile_pattern[8] = {

    0x3C,
    0x42,
    0xA5,
    0x81,
    0xA5,
    0x99,
    0x42,
    0x3C
};

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

    max7219_draw_pattern(smile_pattern);
    delay_ms(APP_SPI_DEMO_PATTERN_DELAY_MS);
}
