# `Dragonfly`

> An embedded C++ drone control application.

## Features

- **Real-time control**: Directly control drone motors and sensors.
- **Embedded systems**: Designed for low-level hardware interaction.
- **C++**: Utilizes modern C++ features for efficient performance.
- **Cross-platform**: Compatible with various embedded systems.

## Installation

1. Clone the repository:

   ```bash
   git clone git@github.com:Gavtriple9/DragonFly.git && cd DragonFly
   ```

2. Install `PlatformIO CLI` or `PlatformIO IDE`:

   - Follow the [PlatformIO installation guide](https://docs.platformio.org/en/latest/core/installation/index.html).

3. Open the project in PlatformIO IDE or use the CLI to build and upload:

   ```bash
    pio run --environment <BOARD_TYPE> --target upload
   ```

   Where `<BOARD_TYPE>` is the target board you are using (e.g., `teensy41`, `esp32dev`, `arduino_uno`, etc.).
