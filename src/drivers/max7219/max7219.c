#include "drivers/max7219/max7219.h"
#include "drivers/max7219/max7219_config.h"
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

static uint8_t max7219_framebuffer[MAX7219_MATRIX_SIZE] = {0U};

static void max7219_map_pixel(
        uint8_t row,
        uint8_t column,
        uint8_t *mapped_row,
        uint8_t *mapped_column
);

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

    for (uint8_t row = 1U; row <= MAX7219_MATRIX_SIZE; row++) {
        
        max7219_framebuffer[row - 1U] = MAX7219_CLEAR_VALUE;
        max7219_write_register(row, MAX7219_CLEAR_VALUE);
    }
}

void max7219_set_row(uint8_t row, uint8_t value) {

    if ((row < 1U) || (row > MAX7219_MATRIX_SIZE)) {

        return;
    }

    max7219_framebuffer[row - 1U] = value;
    max7219_write_register(row, value);
}

void max7219_all_on(void) {

    for (uint8_t row = 1U; row <= MAX7219_MATRIX_SIZE; row++) {

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

void max7219_set_pixel(uint8_t row, uint8_t column, uint8_t enabled) {

    uint8_t mapped_row = 0U;
    uint8_t mapped_column = 0U;

    if ((row < 1U) || (row > MAX7219_MATRIX_SIZE)) {

        return;
    }

    if ((column < 1U) || (column > MAX7219_MATRIX_SIZE)) {

        return;
    }

    max7219_map_pixel(row, column, &mapped_row, &mapped_column);

    const uint8_t row_index = mapped_row - 1U;
    const uint8_t bit_mask = (uint8_t)(1U << (mapped_column - 1U));

    if (enabled != 0U) {

        max7219_framebuffer[row_index] |= bit_mask;
    } else {

        max7219_framebuffer[row_index] &= (uint8_t)(~bit_mask);
    }

    max7219_set_row(mapped_row, max7219_framebuffer[row_index]);
}

void max7219_draw_pattern(const uint8_t pattern[8]) {

    if (pattern == 0) {

        return;
    }

    max7219_clear();

    for (uint8_t row = 1U; row <= MAX7219_MATRIX_SIZE; row++) {

        for (uint8_t column = 1U; column <= MAX7219_MATRIX_SIZE; column++) {

            const uint8_t row_value = pattern[row - 1U];
            const uint8_t bit_mask = (uint8_t)(1U << (column - 1U));

            if ((row_value & bit_mask) != 0U) {

                max7219_set_pixel(row, column, 1U);
            }
        }
    }
}

static void max7219_map_pixel(
        uint8_t row,
        uint8_t column,
        uint8_t *mapped_row,
        uint8_t *mapped_column
) {
    uint8_t logical_row = row;
    uint8_t logical_column = column;

#if (MAX7219_MIRROR_X != 0U)
    logical_column = (MAX7219_MATRIX_SIZE + 1U) - logical_column;
#endif

#if (MAX7219_MIRROR_Y != 0U)
    logical_row = (MAX7219_MATRIX_SIZE + 1U) - logical_row;
#endif

#if (MAX7219_MATRIX_ORIENTATION == MAX7219_ORIENTATION_0)
    *mapped_row = logical_column;
    *mapped_column = logical_row;
#elif (MAX7219_MATRIX_ORIENTATION == MAX7219_ORIENTATION_90)
    *mapped_row = (MAX7219_MATRIX_SIZE + 1U) - logical_row;
    *mapped_column = logical_column;
#elif (MAX7219_MATRIX_ORIENTATION == MAX7219_ORIENTATION_180)
    *mapped_row = (MAX7219_MATRIX_SIZE + 1U) - logical_column;
    *mapped_column = (MAX7219_MATRIX_SIZE + 1U) - logical_row;
#elif (MAX7219_MATRIX_ORIENTATION == MAX7219_ORIENTATION_270)
    *mapped_row = logical_row;
    *mapped_column = (MAX7219_MATRIX_SIZE + 1U) - logical_column;
#else
    *mapped_row = logical_column;
    *mapped_column = logical_row;
#endif
}
