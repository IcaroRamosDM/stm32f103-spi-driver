#pragma once

#include <stddef.h>
#include <stdint.h>

void spi_bus_init(void);

void spi_bus_write_byte(uint8_t data);

void spi_bus_write_register(uint8_t reg, uint8_t value);

void spi_bus_write_buffer(const uint8_t *buffer, size_t length);
