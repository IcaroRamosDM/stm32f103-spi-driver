# STM32F103 SPI + MAX7219 Matrix

[![Checks](https://github.com/IcaroRamosDM/stm32f103-spi-driver/actions/workflows/checks.yml/badge.svg)](https://github.com/IcaroRamosDM/stm32f103-spi-driver/actions/workflows/checks.yml)

Bare-metal SPI1 firmware using libopencm3 and a MAX7219 8×8 matrix.
It separates pin/peripheral setup, bus transactions, display mapping and the demo.

## Features

- SPI mode 0, MSB first and software-controlled chip select.
- Register and buffer transfers.
- An eight-byte display framebuffer, pixel updates and configurable orientation/mirroring.
- Whole-pattern rendering with one write per physical row: eight register writes.
- A demo with corner checks, a pixel walk, patterns, all-on and clear states.

## Build

[Build instructions](docs/build.md)

~~~sh
make all
make test
make sanitize
~~~

## Connections and logic levels

[Wiring](docs/wiring.md) documents the module's IN connector. The STM32 uses
3.3 V logic. The MAX7219 IC specifies a 4.0–5.5 V supply and its input thresholds
must be met; use suitable level translation where required by the module.
A 3.3 V MCU output is not automatically a guaranteed high level for a 5 V module.
See the [manufacturer datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/MAX7219-MAX7221.pdf).

## Documentation

- [Architecture](docs/architecture.md)
- [SPI transaction flow](docs/spi_flow.md)
- [MAX7219 framebuffer and mapping](docs/max7219.md)

## License

[MIT](LICENSE).

## Author

**Icaro Ramos Rodrigues dos Santos**<br>
Electronic Engineer

Embedded Systems | Firmware | C | C++ | Python | Dart | Assembly | Hardware Design | PCB Design | STM32 | ARM Cortex-M | Linux | Windows | RISC-V | Verilog | SystemVerilog | UVM | Design Verification | Instrumentation | Signal Processing | Qt | FLTK

GitHub: [IcaroRamosDM](https://github.com/IcaroRamosDM)<br>
LinkedIn: [icaro-ramos-r](https://www.linkedin.com/in/icaro-ramos-r/)<br>
[icaroelt@gmail.com](mailto:icaroelt@gmail.com)
