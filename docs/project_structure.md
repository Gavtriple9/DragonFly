# DragonFly Project Structure

This document outlines the modular architecture of the DragonFly drone flight controller firmware. The structure is designed with clear separation of concerns, enabling maintainability, testability, and portability across different hardware platforms.

## Overview

The project follows a layered architecture pattern, where each layer has specific responsibilities and dependencies flow in one direction - from higher-level application logic down to hardware abstraction.

```
┌──────────────────────────────────────────────────────────────┐
│                             app/                             │
│                      (Main Application)                      │
├──────────────────────────────────────────────────────────────┤
│    control/      │     sensors/    │     comms/     │ utils/ │
│ (Flight Control) │ (Sensor Fusion) │(Communications)│        │
├──────────────────────────────────────────────────────────────┤
│                           drivers/                           │
│                       (Device Drivers)                       │
├──────────────────────────────────────────────────────────────┤
│                             hal/                             │
│                 (Hardware Abstraction Layer)                 │
└──────────────────────────────────────────────────────────────┘
```

## Module Descriptions

### app/ - Application Layer

**Purpose**: The highest level of the system architecture. Orchestrates the entire system, handles initialization, and manages the main loop or RTOS tasks.

**Responsibilities**:

- System initialization and startup sequence
- Main control loop coordination
- RTOS task management and scheduling
- System-wide error handling and recovery
- Power management and system states
- Coordination between all subsystems

**Dependencies**: All other modules (control, sensors, comms, drivers, hal, utils)

### hal/ - Hardware Abstraction Layer

**Purpose**: Provides a generic interface to the microcontroller's peripherals (GPIO, I2C, SPI, UART, Timers, ADC, Flash).

**Benefit**: Decouples your application code from the specific MCU hardware. If you change microcontrollers, you only need to rewrite the HAL layer, not the drivers or higher-level logic. This is crucial for portability and testability (you can mock HAL functions easily).

**Key Components**:

- `hal_gpio`: GPIO pin control and configuration
- `hal_i2c`: I2C communication interface
- `hal_spi`: SPI communication interface
- `hal_uart`: UART/serial communication
- `hal_timer`: Timer and PWM functionality
- `hal_adc`: Analog-to-digital conversion
- `hal_flash`: Non-volatile memory access

**Dependencies**: None (lowest level)

### drivers/ - Device Drivers

**Purpose**: Implement drivers for specific external components (IMU, Barometer, GPS, RC receiver, ESCs, external flash).

**Dependency**: These drivers use the generic HAL functions to communicate with the hardware. They do not directly access MCU registers.

**Benefit**: Abstracts away the device-specific communication protocols (e.g., I2C commands for MPU6050) from higher layers.

**Key Components**:

- `drv_imu`: Inertial Measurement Unit (accelerometer, gyroscope, magnetometer)
- `drv_barometer`: Pressure sensor for altitude estimation
- `drv_gps`: Global Positioning System interface
- `drv_rc`: Radio control receiver
- `drv_esc`: Electronic Speed Controller interface
- `drv_flash`: External flash memory
- `drv_led`: Status indicator LEDs

**Dependencies**: hal/

### sensors/ - Sensor Processing and Fusion

**Purpose**: Process and fuse raw data from drivers into meaningful estimates (e.g., filtered attitude, estimated altitude, position).

**Dependency**: Uses the drivers layer for raw sensor data.

**Benefit**: Provides clean, high-level sensor data to the control algorithms, making the control logic simpler and less dependent on raw sensor noise.

**Key Components**:

- Sensor data filtering and noise reduction
- Attitude estimation (roll, pitch, yaw)
- Position and velocity estimation
- Altitude estimation and barometric compensation
- Sensor calibration and bias correction
- Sensor fusion algorithms (Kalman filters, complementary filters)

**Dependencies**: drivers/, lib/filters/, lib/math/

### control/ - Flight Control System

**Purpose**: Implements the core flight control algorithms (PID loops for attitude, altitude, position), flight mode management, and motor mixing.

**Dependency**: Relies on processed data from sensors/ and commands motors via drivers/drv_esc.

**Benefit**: The "brain" of the drone. Clear separation of control logic.

**Key Components**:

- Attitude control (stabilization)
- Altitude control (hold, climb/descend)
- Position control (loiter, waypoint navigation)
- Flight mode management (manual, stabilize, altitude hold, GPS modes)
- Motor mixing and output calculation
- Safety systems (failsafe, geofencing)

**Dependencies**: sensors/, drivers/, lib/pid/

### comms/ - Communications

**Purpose**: Handles communication protocols for telemetry, debugging (CLI), and data transfer.

**Dependency**: Uses hal_uart or hal_usb_serial for physical communication.

**Benefit**: Decouples communication logic from flight control.

**Key Components**:

- Telemetry data transmission
- Command and control interface
- Debug console and CLI
- Firmware update protocols
- Data logging communication
- Ground station interface

**Dependencies**: hal/, utils/

### utils/ - Utility Functions

**Purpose**: General-purpose utility functions and data structures that are not specific to any particular drone subsystem (e.g., data logging, parameter storage, common math helpers, queues).

**Benefit**: Prevents code duplication and provides common, reusable building blocks.

**Key Components**:

- Data structures (rings buffers, queues, lists)
- Mathematical utilities
- String manipulation and formatting
- Parameter storage and retrieval
- Data logging utilities
- Memory management helpers
- Debug and diagnostic tools

**Dependencies**: hal/ (for flash/EEPROM access)

## Library Modules (lib/)

### lib/filters/

- Extended Kalman Filter (EKF) implementation
- Complementary filters
- Low-pass, high-pass, and band-pass filters
- Sensor-specific filtering algorithms

### lib/math/

- Quaternion mathematics for attitude representation
- Vector and matrix operations
- Trigonometric functions and optimizations
- Mathematical constants and utilities

### lib/pid/

- PID controller implementation
- Tuning parameter management
- Anti-windup and saturation handling
- Multiple PID controller instances

## Design Principles

1. **Separation of Concerns**: Each module has a single, well-defined responsibility
2. **Dependency Inversion**: Higher-level modules depend on abstractions, not concretions
3. **Portability**: HAL layer enables easy porting to different microcontrollers
4. **Testability**: Clear interfaces allow for unit testing and mocking
5. **Maintainability**: Modular design makes code easier to understand and modify
6. **Reusability**: Common functionality is centralized in utils and lib modules

## Data Flow

```
Raw Sensor Data → drivers/ → sensors/ → control/ → drivers/ → Motor Outputs
                     ↓         ↓          ↓
                   hal/    lib/filters  lib/pid
                     ↓         ↓          ↓
                Hardware   Processed   Control
                           Data       Signals
```

This architecture ensures that the flight control system is robust, maintainable, and adaptable to different hardware configurations while maintaining clean separation between different functional areas.
