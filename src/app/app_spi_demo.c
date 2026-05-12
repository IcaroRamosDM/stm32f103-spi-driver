#include "app/app_spi_demo.h"

#include "bsp/gpio.h"
#include "bsp/systick.h"

#include "drivers/max7219/max7219.h"

#define APP_SPI_DEMO_PATTERN_DELAY_MS      1000U
#define APP_SPI_DEMO_PIXEL_DELAY_MS         100U
#define APP_SPI_DEMO_MATRIX_SIZE              8U

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

static void app_spi_demo_pixel_walk(void);

void app_spi_demo_run(void) {

    gpio_led_toggle();

    max7219_clear();
    max7219_set_pixel(1U, 1U, 1U);
    delay_ms(APP_SPI_DEMO_PATTERN_DELAY_MS);

    max7219_clear();
    max7219_set_pixel(1U, 8U, 1U);
    delay_ms(APP_SPI_DEMO_PATTERN_DELAY_MS);

    max7219_clear();
    max7219_set_pixel(8U, 1U, 1U);
    delay_ms(APP_SPI_DEMO_PATTERN_DELAY_MS);

    max7219_clear();
    max7219_set_pixel(8U, 8U, 1U);
    delay_ms(APP_SPI_DEMO_PATTERN_DELAY_MS);

    app_spi_demo_pixel_walk();

    max7219_clear();
    max7219_draw_pattern(smile_pattern);
    delay_ms(APP_SPI_DEMO_PATTERN_DELAY_MS);

    max7219_clear();
    max7219_all_on();
    delay_ms(APP_SPI_DEMO_PATTERN_DELAY_MS);

    max7219_clear();
    max7219_checkerboard();
    delay_ms(APP_SPI_DEMO_PATTERN_DELAY_MS);

    max7219_clear();
    delay_ms(APP_SPI_DEMO_PATTERN_DELAY_MS);
}

static void app_spi_demo_pixel_walk(void) {

    max7219_clear();

    for (uint8_t row = 1U; row <= APP_SPI_DEMO_MATRIX_SIZE; row++) {

        for (uint8_t column = 1U; column <= APP_SPI_DEMO_MATRIX_SIZE; column++) {

            max7219_set_pixel(row, column, 1U);
            delay_ms(APP_SPI_DEMO_PIXEL_DELAY_MS);
            max7219_set_pixel(row, column, 0U);

        }
    }
}
