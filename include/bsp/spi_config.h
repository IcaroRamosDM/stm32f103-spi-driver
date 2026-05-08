#pragma once

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>

#define BSP_SPI_PORT            SPI1

#define BSP_SPI_RCC             RCC_SPI1
#define BSP_SPI_GPIO_RCC        RCC_GPIOA

#define BSP_SPI_GPIO_PORT       GPIOA

#define BSP_SPI_SCK_PIN         GPIO5
#define BSP_SPI_MOSI_PIN        GPIO7
#define BSP_SPI_CS_PIN          GPIO4
