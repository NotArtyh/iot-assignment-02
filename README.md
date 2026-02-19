# Assignment #02 - Smart Drone Hangar - IoT Embedded Systems Year: 2025/2026

- [assignment instructions](https://github.com/pslab-unibo/esiot-2025-2026/blob/master/assignments/assignment-02.md)

## Authors

- Muller Arthur Istvan \
   Matricola: 0001145303
- Cattolico Giuseppe \
   Matricola: 0001124318

link uml diagrams: https://lucid.app/lucidchart/5d4fabe1-c16f-4353-b877-1f1fa4a3f847/edit?viewport_loc=-4363%2C-1797%2C10358%2C4188%2C0m8xT1A-z0s.&invitationId=inv_bbe5bf6e-1e22-4480-a804-d33e2b081425

## Setup and Build

The project has been tested and has native support for the following `i2c` displays:

- LCD - `1602 lcd`
- OLED - `sh1106 oled`

Any display using the i2c protocol and supported by the `LiquidCrystal_I2C.h` library for LCDs or the `U8g2lib.h` for the OLEDs (virtually any oled display with any protocol is supported with this library) should work with minimal editing of the respective display module.

To switch between the OLED and LCD configuration, set the `-D USE_OLED` build flag in the `platformio.ini` (or configure a platformio env with the corresonding flag)

## Project Architecture
