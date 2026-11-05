#include "drivers/max7219/max7219.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint8_t registers[16];
static unsigned writes;

static void check(bool condition, const char *expression, int line) {
    if (!condition) {
        fprintf(stderr, "test_max7219.c:%d: %s\n", line, expression);
        exit(EXIT_FAILURE);
    }
}

#define CHECK(condition) check((condition), #condition, __LINE__)

void spi_bus_write_register(uint8_t reg, uint8_t value) {
    CHECK(reg < sizeof registers);
    registers[reg] = value;
    writes++;
}

int main(void) {
    max7219_clear();
    CHECK(writes == 8U);
    max7219_set_pixel(1U, 1U, 1U);
    CHECK(registers[1] == 0x01U);
    max7219_set_pixel(2U, 3U, 1U);
    CHECK(registers[3] == 0x02U);
    max7219_set_pixel(2U, 3U, 0U);
    CHECK(registers[3] == 0U);

    unsigned previous_writes = writes;
    max7219_set_pixel(0U, 1U, 1U);
    max7219_set_pixel(1U, 9U, 1U);
    max7219_set_row(9U, 0xFFU);
    max7219_draw_pattern(NULL);
    CHECK(writes == previous_writes);

    const uint8_t filled[8] = {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};
    previous_writes = writes;
    max7219_draw_pattern(filled);
    CHECK(writes - previous_writes == 8U);
    for (unsigned row = 1U; row <= 8U; row++) {
        CHECK(registers[row] == 0xFFU);
    }

    const uint8_t corner[8] = {0x01U};
    max7219_draw_pattern(corner);
    CHECK(registers[1] == 0x01U);
    for (unsigned row = 2U; row <= 8U; row++) {
        CHECK(registers[row] == 0U);
    }
    puts("PASS: default orientation, pixel bounds and eight-write pattern flush");
    return EXIT_SUCCESS;
}
