# DragonFly Logging System

This logging system provides platform-specific logging macros that automatically adapt based on the build environment.

## Features

- **Platform-aware**: Automatically selects appropriate logging backend based on build environment
- **Native Environment**: Uses spdlog for rich logging with file output
- **Teensy41 Environment**: Uses Serial output with formatted messages
- **Consistent API**: Same logging macros work across all platforms

## Build Environments

### Native Environment (`BUILD_ENV_NAME=100`)

- Uses spdlog library
- Logs to both console and file (`logs/dragonfly.log`)
- Supports all log levels with formatting
- Automatic log rotation (daily files)
- Colored console output

### Teensy41 Environment (`BUILD_ENV_NAME=101`)

- Uses Arduino Serial interface
- Formatted output to serial monitor
- Supports printf-style formatting
- Configurable baud rate via `BAUD_RATE` in config.h

## Usage

### Initialization

```cpp
#include "logging.h"

void setup() {
    // Initialize the logging system
    init_logger();
}
```

### Basic Logging

```cpp
INFO("System startup complete");
WARN("Low battery voltage detected");
ERROR("Sensor initialization failed");
DEBUG("Loop iteration: {}", iteration_count);
TRACE("Entering function: calculate_position");
```

### Formatted Logging

```cpp
// Single parameter
INFO("Temperature: {} degrees", temperature);

// Multiple parameters
INFO("Position: x={}, y={}, z={}", pos_x, pos_y, pos_z);

// Mixed types
WARN("Sensor {} failed with error code {}", sensor_name, error_code);
```

### Available Log Levels

1. **TRACE**: Finest level of detail (function entry/exit, etc.)
2. **DEBUG**: Detailed diagnostic information
3. **INFO**: General information about program execution
4. **WARN**: Potentially harmful situations
5. **ERROR**: Error events that don't stop execution

## Log Format

### Native Environment

```
[2025-06-18 10:30:45.123] [info] System startup complete
[2025-06-18 10:30:45.124] [warn] Low battery voltage detected
[2025-06-18 10:30:45.125] [error] Sensor initialization failed
```

### Teensy41 Environment

```
[INFO] System startup complete
[WARN] Low battery voltage detected
[ERROR] Sensor initialization failed
```

## Configuration

### Native Environment

- Log files are stored in `logs/` directory
- Default log level: INFO
- Automatic flush on WARN level and above
- Daily log rotation

### Teensy41 Environment

- Baud rate configured via `BAUD_RATE` in `config.h`
- Serial monitor required to view logs
- No log persistence (output only)

## Best Practices

1. **Initialize Early**: Call `init_logger()` as early as possible in your application
2. **Use Appropriate Levels**:
   - Use INFO for normal operation status
   - Use WARN for recoverable issues
   - Use ERROR for serious problems
   - Use DEBUG for development/troubleshooting
   - Use TRACE for very detailed debugging
3. **Format Messages**: Use the formatting capabilities instead of string concatenation
4. **Conditional Logging**: For expensive operations, consider wrapping in conditions

## Example Integration

```cpp
#include "logging.h"

class FlightController {
public:
    void initialize() {
        init_logger();
        INFO("Flight controller initializing...");

        if (!initialize_sensors()) {
            ERROR("Sensor initialization failed");
            return;
        }

        INFO("Flight controller ready");
    }

    void update() {
        static int loop_count = 0;

        if (++loop_count % 1000 == 0) {
            DEBUG("Control loop: {}", loop_count);
        }

        // ... flight control logic ...
    }
};
```

## Platform Detection

The logging system automatically detects the build environment using preprocessor macros:

- `BUILD_ENV_NAME == native_env` (100): Desktop/native development
- `BUILD_ENV_NAME == teensy41` (101): Teensy 4.1 microcontroller

## File Structure

- `include/logging.h`: Main header with platform-specific macros
- `src/utils/logging.cpp`: Implementation of logging functions
- `src/utils/logging_demo.cpp`: Usage examples and demonstrations
