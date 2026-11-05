# SPI transaction flow

The bus selects the device, transmits the register address and value MSB first,
and releases chip select. SPI1 uses mode 0 and a peripheral-clock divisor of 16.
The hardware clock and resulting SCK depend on the board clock configuration.

The MAX7219 adapter uses this two-byte write transaction. Register reads are not
implemented by the display protocol. Host tests observe the register/value pairs;
an instrument is needed to inspect real SCK, MOSI and chip-select timing.
