#pragma once

#include <stdint.h>

void max7219_write_register(uint8_t reg, uint8_t value);
void max7219_init(void);
void max7219_clear(void);

void max7219_set_row(uint8_t row, uint8_t value);
void max7219_all_on(void);
void max7219_checkerboard(void);
