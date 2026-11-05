# Wiring and supply

Use the module's IN connector.

| STM32F103 | MAX7219 module |
|---|---|
| PA5 | CLK, through suitable level translation if required |
| PA7 | DIN, through suitable level translation if required |
| PA4 | CS/LOAD, through suitable level translation if required |
| GND | GND |

Supply the module according to its specification. The MAX7219 IC's documented
operating supply is 4.0–5.5 V; do not assume the IC is specified for 3.3 V supply.
The STM32 signals are 3.3 V and must meet the module's input-high thresholds.
A direct connection to a 5 V MAX7219 is not a guaranteed logic-level interface.

[Analog Devices datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/MAX7219-MAX7221.pdf).
The DOUT connector is for chaining another display, not the input to this demo.
