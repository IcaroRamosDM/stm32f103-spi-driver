# Architecture

Board code configures clocks, SPI1 and chip select. spi_bus.c provides byte,
register and buffer transfers. max7219.c owns the display framebuffer and logical
pixel mapping. The application selects demonstration patterns.

Pixel updates modify one mapped physical row. Whole-pattern drawing first builds
the complete framebuffer and then writes each of the eight rows once.
