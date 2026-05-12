# Hardware Wiring

## Overview

This project uses SPI1 from STM32F103C8T6 to communicate with a MAX7219 8x8 LED matrix module.

The module is used as a real SPI peripheral validation target.

The connection is simple but small mistakes commonly cause complete communication failure.

Typical mistakes:

- wrong side of the module
- DIN connected incorrectly
- missing GND
- wrong VCC assumptions
- CS connected to wrong pin

This document exists to avoid those problems.

---

## STM32 SPI1 Pins

This project uses:

| STM32 Pin | Function |
|---|---|
| PA5 | SPI1 SCK |
| PA7 | SPI1 MOSI |
| PA4 | Manual CS |
| GND | Common ground |
| 3V3 / 5V | Power |

Only transmit is required.

MISO is not used.

---

## MAX7219 Module Pins

Most modules expose two sides:

```text
IN
OUT
```

Only:

```text
IN
```

is used for a single matrix module.

The:

```text
OUT
```

side is only required for daisy-chain configurations.

This project uses a single module only.

---

## Correct Connection

### Side used

Use:

```text
IN
```

pins only.

Typical labels:

```text
CLK
CS
DIN
GND
VCC
```

Connection:

| STM32 | MAX7219 |
|---|---|
| PA5 | CLK |
| PA7 | DIN |
| PA4 | CS |
| GND | GND |
| 3V3 or 5V | VCC |

Important:

```text
DIN = input
DOUT = output for chaining
```

Do not connect to:

```text
DOUT
```

for a single-module setup.

This is a very common mistake.

---

## Why DOUT Exists

The MAX7219 supports cascaded modules.

Example:

```text
STM32 → Module 1 → Module 2 → Module 3
```

using:

```text
DOUT → DIN
```

between modules.

This project does not use cascading.

Therefore:

```text
DOUT remains unused
```

and should be left disconnected.

---

## Connector Recommendation

Recommended assembly:

```text
IN  → straight header
OUT → not populated
```

Reason:

- cleaner wiring
- simpler debugging
- fewer unnecessary solder joints

The `OUT` connector is optional for future expansion.

For this project it is unnecessary.

---

## Power Supply

Many MAX7219 modules work more reliably with:

```text
5V
```

even when driven by:

```text
3.3V logic
```

from STM32.

Typical working setup:

```text
MAX7219 VCC = 5V
STM32 GPIO = 3.3V
Common GND shared
```

This usually works correctly.

---

## Important Safety Rule

Do not assume:

```text
all modules behave identically
```

Some boards tolerate:

```text
3.3V VCC
```

Some behave poorly.

Some require:

```text
5V VCC
```

Validation should always be practical, not assumed.

---

## Module Orientation

Many matrix modules are mounted with different physical rotations depending on manufacturer.

This affects:

```c
max7219_set_pixel()
```

visual output.

Example:

```c
max7219_set_pixel(1,1,1);
```

may not light the top-left LED physically.

This is not a wiring problem.

It is a module assembly variation.

The driver solves this using:

```c
MAX7219_MATRIX_ORIENTATION
MAX7219_MIRROR_X
MAX7219_MIRROR_Y
```

This keeps the public API stable.

---

## Practical Validation

The recommended validation order:

### Step 1

Power + SPI bring-up

Expected:

```text
no reset loops
no unstable behavior
```

---

### Step 2

All LEDs ON

```c
max7219_all_on();
```

Expected:

```text
entire matrix lights
```

This validates:

- power
- SPI communication
- CS timing

---

### Step 3

Corner validation

```c
(1,1)
(1,8)
(8,1)
(8,8)
```

This validates:

- orientation
- axis direction
- mirror correctness

---

### Step 4

Pixel walk

Expected:

```text
left → right
top → bottom
```

This validates coordinate consistency.

---

## Common Failure Cases

---

### Nothing lights

Usually caused by:

- wrong VCC
- missing GND
- wrong IN/OUT side
- CS disconnected
- wrong SPI mode

---

### Only random LEDs light

Usually caused by:

- unstable power
- wrong CPOL/CPHA
- incorrect CS timing

---

### Smile appears rotated

Usually caused by:

- orientation mismatch

Not:

- bad SPI communication

This should be solved in software, not rewiring.

---

## Final Recommendation

Always validate:

```text
hardware first
software second
```

Do not debug orientation before confirming:

```text
SPI communication is working correctly
```

This saves significant development time.
