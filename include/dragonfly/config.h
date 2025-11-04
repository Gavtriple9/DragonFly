#pragma once
#include "environment.h"

// --------------------- Global configuration settings -------------------- //
#define BAUD_RATE 115200
// ------------------------------------------------------------------------ //

// ----------------------------- Sensor types ----------------------------- //
#define SYNTHETIC_SENSOR 0x0000
// Arm
#define GPIO_PIN 0x1001
// IMUs
#define MPU9250 0x2001
// Altitude
#define BMP388 0x3001
// Position
#define GPS_UBLOX 0x4001
// Optical
#define OPTICAL_FLOW 0x5001
// Ultrasonic
#define ULTRASONIC 0x6001
// ------------------------------------------------------------------------ //

#if BUILD_ENV_NAME == native_env
#   define ORIENTATION_SENSOR SYNTHETIC_SENSOR
#   define ALTITUDE_SENSOR SYNTHETIC_SENSOR
#   define ARM_SENSOR SYNTHETIC_SENSOR
#elif BUILD_ENV_NAME == teensy41
#   define ORIENTATION_SENSOR MPU9250
#   define ALTITUDE_SENSOR BMP388
#   define ARM_SENSOR GPIO_PIN
#endif