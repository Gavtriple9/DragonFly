# GPIO Hardware Abstraction Layer (HAL) Documentation

## Overview

The GPIO HAL provides a unified interface for GPIO operations across different microcontroller platforms. This implementation is specifically designed for the Teensy 4.1 but can be easily ported to other platforms by implementing the hardware-specific portions while maintaining the same API.

## Architecture

### Abstraction Levels

```
┌─────────────────────────────────────────┐
│           Application Code              │
├─────────────────────────────────────────┤
│         GPIO HAL Interface              │  ← Platform Independent
├─────────────────────────────────────────┤
│      Teensy 4.1 Implementation         │  ← Platform Specific
├─────────────────────────────────────────┤
│        Hardware Registers              │
└─────────────────────────────────────────┘
```

### Key Features

1. **Platform Abstraction**: Same API works across different MCUs
2. **Direct Register Access**: Maximum performance using direct register manipulation
3. **Arduino Pin Compatibility**: Uses familiar Arduino pin numbering
4. **Advanced Features**: Access to platform-specific features (drive strength, slew rate)
5. **Interrupt Support**: Unified interrupt handling interface
6. **Type Safety**: Strong typing with enums to prevent configuration errors

## API Reference

### Initialization

```cpp
#include "hal/hal_gpio.hpp"
using namespace df::hal;

// Initialize the GPIO HAL - call once at startup
bool success = GPIO::init();
```

### Pin Configuration

```cpp
// Basic pin modes
GPIO::configurePin(13, PinMode::OUTPUT);           // Standard output
GPIO::configurePin(2, PinMode::INPUT);             // High-impedance input
GPIO::configurePin(3, PinMode::INPUT_PULLUP);      // Input with pull-up
GPIO::configurePin(4, PinMode::INPUT_PULLDOWN);    // Input with pull-down
GPIO::configurePin(5, PinMode::OUTPUT_OPENDRAIN);  // Open-drain output

// Advanced configuration (Teensy 4.1 specific)
GPIO::configurePinAdvanced(13, DriveStrength::HIGH, SlewRate::FAST);
```

### Digital I/O

```cpp
// Write to pins
GPIO::writePin(13, PinState::HIGH);  // Set pin high
GPIO::writePin(13, PinState::LOW);   // Set pin low
GPIO::togglePin(13);                 // Toggle pin state

// Read from pins
PinState state = GPIO::readPin(2);
if (state == PinState::HIGH) {
    // Pin is high
}
```

### Interrupts

```cpp
// Define interrupt callback
void myInterruptHandler() {
    Serial.println("Interrupt triggered!");
}

// Attach interrupt
GPIO::attachInterrupt(2, InterruptMode::FALLING, myInterruptHandler);

// Detach interrupt
GPIO::detachInterrupt(2);
```

### Port Operations (Advanced)

```cpp
// Atomic multi-pin operations
uint32_t pin_mask = (1 << 2) | (1 << 3) | (1 << 4);  // Pins 2, 3, 4
uint32_t values = (1 << 2) | (1 << 4);               // Set pins 2,4 high, 3 low
GPIO::writePort(pin_mask, values);

// Read multiple pins
uint32_t current_states = GPIO::readPort(pin_mask);
```

## Teensy 4.1 Implementation Details

### GPIO Port Mapping

The Teensy 4.1 has 9 GPIO ports (GPIO1-GPIO9). The implementation maps Arduino pin numbers to the appropriate GPIO port and bit position:

```cpp
// Example mappings:
Pin 0  → GPIO1, bit 3
Pin 13 → GPIO2, bit 3  (Built-in LED)
Pin 2  → GPIO1, bit 4
...
```

### Register Access

Direct register access is used for maximum performance:

```cpp
// Example: Writing to pin 13 (GPIO2, bit 3)
GPIO2_DR |= (1 << 3);   // Set bit 3 high
GPIO2_DR &= ~(1 << 3);  // Set bit 3 low
```

### Advanced Features

The Teensy 4.1 supports advanced pad configuration:

- **Drive Strength**: Controls output current capability (1.8mA to 5.2mA)
- **Slew Rate**: Controls transition speed (affects EMI)
- **Pull Resistors**: Internal pull-up/down resistors
- **Open Drain**: True open-drain outputs
- **Hysteresis**: Input noise immunity

## Porting to Other Platforms

To port this HAL to another microcontroller:

### 1. Update Pin Mapping

Modify the `pin_mapping` table to reflect your MCU's pin layout:

```cpp
static const PinMapping pin_mapping[MAX_PINS] = {
    // Your MCU's pin mappings here
};
```

### 2. Update Register Addresses

Modify the port base addresses and register offsets:

```cpp
static volatile uint32_t* const gpio_port_bases[] = {
    // Your MCU's GPIO base addresses
};
```

### 3. Implement Platform-Specific Functions

Update these functions for your platform:

- `getPortRegisters()`
- `getPinMuxRegister()`
- `getPinPadRegister()`
- `configurePinAdvanced()` (if supported)

### 4. Update Constants

Modify the constants to match your platform:

```cpp
static constexpr uint8_t MAX_PIN_NUMBER = 41;  // Your max pin
static constexpr uint8_t NUM_PORTS = 9;       // Your port count
```

## Example Platforms

### ESP32

```cpp
// ESP32 would use different base addresses
#define GPIO_BASE_REG 0x3FF44000
```

### STM32F4

```cpp
// STM32 would use GPIOA, GPIOB, etc.
static volatile uint32_t* const gpio_port_bases[] = {
    GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH
};
```

### Arduino Uno (ATmega328P)

```cpp
// AVR would use PORT/PIN/DDR registers
// Different approach needed due to 8-bit architecture
```

## Performance Considerations

### Direct Register Access

- **Advantage**: Fastest possible GPIO operations
- **Disadvantage**: Platform-specific, more complex

### Arduino Functions Comparison

```cpp
// Traditional Arduino (slower)
digitalWrite(13, HIGH);

// Our HAL (faster)
GPIO::writePin(13, PinState::HIGH);

// Direct register (fastest, but not portable)
GPIO2_DR |= (1 << 3);
```

### Atomic Operations

The HAL provides atomic multi-pin operations which are faster than multiple single-pin operations and prevent race conditions.

## Error Handling

The HAL includes comprehensive error checking:

```cpp
// All functions return success/failure status
if (!GPIO::configurePin(99, PinMode::OUTPUT)) {
    Serial.println("Invalid pin number!");
}

// Pin validation
if (GPIO::isPinValid(pin)) {
    // Pin is valid for this platform
}
```

## Thread Safety

**Important**: This implementation is **not** thread-safe. If using with RTOS or interrupts:

1. Disable interrupts during critical sections
2. Use mutex/semaphore protection
3. Consider atomic operations for simple pin toggles

## Usage Examples

### Basic LED Blink

```cpp
void setup() {
    GPIO::init();
    GPIO::configurePin(13, PinMode::OUTPUT);
}

void loop() {
    GPIO::writePin(13, PinState::HIGH);
    delay(500);
    GPIO::writePin(13, PinState::LOW);
    delay(500);
}
```

### Button with Interrupt

```cpp
void buttonPressed() {
    Serial.println("Button pressed!");
    GPIO::togglePin(13);  // Toggle LED
}

void setup() {
    GPIO::init();
    GPIO::configurePin(13, PinMode::OUTPUT);
    GPIO::configurePin(2, PinMode::INPUT_PULLUP);
    GPIO::attachInterrupt(2, InterruptMode::FALLING, buttonPressed);
}
```

### High-Performance Pin Bank

```cpp
void updateLEDArray(uint8_t pattern) {
    uint32_t pin_mask = 0xFF << 2;  // Pins 2-9
    uint32_t values = pattern << 2;
    GPIO::writePort(pin_mask, values);  // Update all 8 LEDs atomically
}
```

## Conclusion

This GPIO HAL provides a clean abstraction that maintains high performance while being portable across platforms. The Teensy 4.1 implementation demonstrates how to leverage advanced MCU features while keeping the interface simple and familiar to Arduino users.
