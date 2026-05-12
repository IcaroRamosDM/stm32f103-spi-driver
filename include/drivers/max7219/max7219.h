#pragma once

#include <stdint.h>

void max7219_write_register(uint8_t reg, uint8_t value);
void max7219_init(void);
void max7219_clear(void);
