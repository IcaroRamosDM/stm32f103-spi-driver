# STM32F103 SPI Driver + MAX7219 Matrix

Bare-metal SPI driver implementation for STM32F103C8T6 (Blue Pill) using libopencm3.

This project demonstrates a complete SPI architecture built from scratch, including:

- SPI1 bring-up
- Manual chip select control
- Generic SPI bus driver
- MAX7219 register communication
- 8x8 LED matrix control
- Pixel-level matrix API
- Orientation and mirror mapping
- Framebuffer-based partial updates
- Custom startup file and vector table
- Professional firmware layering (BSP + Driver + App)

This repository is intended for:

- Embedded systems portfolio
- Firmware engineering study
- Bare-metal ARM Cortex-M learning
- SPI architecture reference for future projects

---

## Features

### Core firmware

- STM32F103C8T6 bare-metal firmware
- libopencm3 framework
- Custom linker script
- Custom startup file
- Manual vector table configuration
- SysTick timing base
- GPIO abstraction layer
- Onboard LED control (PC13)

### SPI architecture

- SPI1 master configuration
- Manual CS (chip select) control
- Software slave management (NSS)
- SPI Mode 0 configuration
- Generic SPI transaction layer
- Register write API
- Buffer write API
- Reusable peripheral communication model

### MAX7219 driver

- MAX7219 initialization sequence
- Register-based communication
- Matrix row control
- `max7219_set_pixel()`
- `max7219_draw_pattern()`
- Internal framebuffer
- Configurable orientation mapping
- Configurable mirror X / mirror Y

### Interactive demo

Matrix validation sequence:

- Corner validation
- Pixel walk
- Smile pattern
- All LEDs ON
- Checkerboard
- Clear display

---

## Hardware

### Target board

- STM32F103C8T6 (Blue Pill)

### SPI peripheral

- MAX7219 8x8 LED matrix module

### Programming interface

- ST-Link V2

Optional:

- Breadboard
- Jumper wires

---

## Wiring

### SPI1 + MAX7219

| STM32 | Function | MAX7219 |
|---|---|---|
| PA5 | SCK | CLK |
| PA7 | MOSI | DIN |
| PA4 | CS | CS |
| GND | GND | GND |
| 3V3 / 5V | Power | VCC |

Important:

Use only the:

```text
IN
```

side of the module.

Do **not** use:

```text
DOUT
```

for a single matrix setup.

More details:

See:

```text
docs/wiring.md
```

---

## Build

### Requirements

- arm-none-eabi-gcc
- libopencm3
- st-flash
- openocd

### Build firmware

```bash
make clean
make
```

### Flash firmware

```bash
make flash
```

### Erase flash

```bash
make erase
```

### Reflash

```bash
make reflash
```

---

## Validation Demo

### Corner validation

```c
max7219_set_pixel(1, 1, 1);
max7219_set_pixel(1, 8, 1);
max7219_set_pixel(8, 1, 1);
max7219_set_pixel(8, 8, 1);
```

This validates:

- axis direction
- orientation correctness
- mirror correctness

### Pixel walk

Expected behavior:

```text
left → right
top → bottom
```

This validates logical coordinate consistency.

### Visual patterns

```text
smile
all on
checkerboard
clear
```

These validate framebuffer correctness and reusable API behavior.

---

## Example

Demo sequence:

```text
corner validation
→ pixel walk
→ smile
→ all LEDs ON
→ checkerboard
→ clear
→ loop
```

This confirms:

- SPI communication
- MAX7219 initialization
- coordinate mapping
- framebuffer consistency
- orientation correctness

---

## Project Structure

```text
include/
├── app/
├── bsp/
└── drivers/
    ├── spi/
    └── max7219/

src/
├── app/
├── bsp/
└── drivers/
    ├── spi/
    └── max7219/

startup/
linker/
docs/
```

---

## Documentation

Detailed technical explanations:

- `docs/wiring.md`
- `docs/architecture.md`
- `docs/spi_flow.md`
- `docs/max7219.md`

These documents explain:

- SPI communication flow
- CS / SCK / MOSI / NSS
- SPI mode and transaction design
- MAX7219 register model
- framebuffer strategy
- orientation and mirror mapping
- hardware validation strategy
- firmware architecture decisions

---

## License

MIT License

---

## Author

**Icaro Ramos Rodrigues dos Santos**

Embedded Systems | Firmware | C | Hardware Design | STM32 | ARM Cortex-M | Linux | Verilog | UVM | Design Verification<br><br>
GitHub: https://github.com/IcaroRamosDM<br>
LinkedIn: https://www.linkedin.com/in/icaro-ramos-r/<br>
icaroelt@gmail.com
