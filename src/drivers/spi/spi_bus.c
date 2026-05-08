#include "drivers/spi/spi_bus.h"
#include "bsp/spi.h"

void spi_bus_init(void) {

    spi_setup();
}

void spi_bus_write_byte(uint8_t data) {

    spi_cs_select();
    spi_transfer_byte(data);
    spi_cs_deselect();
}

void spi_bus_write_register(uint8_t reg, uint8_t value) {

    spi_cs_select();

    spi_transfer_byte(reg);
    spi_transfer_byte(value);

    spi_cs_deselect();
}

void spi_bus_write_buffer(const uint8_t *buffer, size_t length) {

    if ((buffer == 0) || (length == 0U)) {

        return;
    }

    spi_cs_select();

    for (size_t i = 0; i < length; i++) {

        spi_transfer_byte(buffer[i]);
    }

    spi_cs_deselect();
}
