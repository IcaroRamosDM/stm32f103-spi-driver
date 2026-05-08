#include "bsp/spi.h"
#include "bsp/spi_config.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>

void spi_setup(void) {

    rcc_periph_clock_enable(BSP_SPI_GPIO_RCC);
    rcc_periph_clock_enable(BSP_SPI_RCC);

    gpio_set_mode(
            BSP_SPI_GPIO_PORT,
            GPIO_MODE_OUTPUT_50_MHZ,
            GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
            BSP_SPI_SCK_PIN | BSP_SPI_MOSI_PIN
    );

    gpio_set_mode(
            BSP_SPI_GPIO_PORT,
            GPIO_MODE_OUTPUT_50_MHZ,
            GPIO_CNF_OUTPUT_PUSHPULL,
            BSP_SPI_CS_PIN
    );

    spi_init_master(
            BSP_SPI_PORT,
            SPI_CR1_BAUDRATE_FPCLK_DIV_16,
            SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
            SPI_CR1_CPHA_CLK_TRANSITION_1,
            SPI_CR1_DFF_8BIT,
            SPI_CR1_MSBFIRST
    );

    spi_enable_software_slave_management(BSP_SPI_PORT);
    spi_set_nss_high(BSP_SPI_PORT);

    spi_enable(BSP_SPI_PORT);

    spi_cs_deselect();
}

void spi_cs_select(void) {

    gpio_clear(BSP_SPI_GPIO_PORT, BSP_SPI_CS_PIN);
}

void spi_cs_deselect(void) {

    gpio_set(BSP_SPI_GPIO_PORT, BSP_SPI_CS_PIN);
}

uint8_t spi_transfer_byte(uint8_t data) {

    spi_send(BSP_SPI_PORT, data);

    return (uint8_t)spi_read(BSP_SPI_PORT);
}
