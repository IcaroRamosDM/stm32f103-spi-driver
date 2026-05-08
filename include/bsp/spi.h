#pragma once

#include <stdint.h>

void spi_setup(void);

void spi_cs_select(void);
void spi_cs_deselect(void);

uint8_t spi_transfer_byte(uint8_t data);
