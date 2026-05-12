#include "drivers/max7219/max7219.h"
#include "drivers/max7219/max7219_registers.h"
#include "drivers/spi/spi_bus.h"

#define MAX7219_INTENSITY_VALUE         0x08U
#define MAX7219_SCAN_ALL_DIGITS         0x07U
#define MAX7219_NORMAL_OPERATION        0x01U
#define MAX7219_SHUTDOWN_DISABLE        0x00U
#define MAX7219_DISPLAY_TEST_DISABLE    0x00U

#define MAX7219_CLEAR_VALUE             0x00U
#define MAX7219_FIRST_DIGIT_REG         MAX7219_REG_DIGIT0
#define MAX7219_LAST_DIGIT_REG          MAX7219_REG_DIGIT7

void max7219_write_register(uint8_t reg, uint8_t value) {

    spi_bus_write_register(reg, value);
}

void max7219_init(void) {

    max7219_write_register(
            MAX7219_REG_DISPLAY_TEST,
            MAX7219_DISPLAY_TEST_DISABLE
    );

    max7219_write_register(
            MAX7219_REG_DECODE_MODE,
            0x00u
    );

    max7219_write_register(
            MAX7219_REG_SCAN_LIMIT,
            MAX7219_SCAN_ALL_DIGITS
    );

    max7219_write_register(
            MAX7219_REG_INTENSITY,
            MAX7219_INTENSITY_VALUE
    );

    max7219_write_register(
            MAX7219_REG_SHUTDOWN,
            MAX7219_NORMAL_OPERATION
   );

    max7219_clear();
}

void max7219_clear(void) {

    for (uint8_t reg = MAX7219_FIRST_DIGIT_REG;
            reg <= MAX7219_LAST_DIGIT_REG;
            reg++) {
        
        max7219_write_register(reg, MAX7219_CLEAR_VALUE);
    }
}

void max7219_set_row(uint8_t row, uint8_t value) {

    if ((row < 1U) || (row > 8U)) {

        return;
    }

    max7219_write_register(row, value);
}

void max7219_all_on(void) {

    for (uint8_t row = 1U; row <= 8U; row++) {

        max7219_set_row(row, 0xFFU);
    }
}

void max7219_checkerboard(void) {

    max7219_set_row(1U, 0xAAU);
    max7219_set_row(2U, 0x55U);
    max7219_set_row(3U, 0xAAU);
    max7219_set_row(4U, 0x55U);
    max7219_set_row(5U, 0xAAU);
    max7219_set_row(6U, 0x55U);
    max7219_set_row(7U, 0xAAU);
    max7219_set_row(8U, 0x55U);
}
