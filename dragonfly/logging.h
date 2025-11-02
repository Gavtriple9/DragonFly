#pragma once

#include "environment.h"

#if BUILD_ENV_NAME == native_env
// Native environment using spdlog
#include "spdlog/spdlog.h"
#include <memory>

// Global logger instance
extern std::shared_ptr<spdlog::logger> g_logger;

// Initialize logger function
void init_logger();

// Logging macros for native environment
#define LOG_INFO(msg, ...) \
    if (g_logger)          \
    g_logger->info(msg, ##__VA_ARGS__)
#define LOG_WARN(msg, ...) \
    if (g_logger)          \
    g_logger->warn(msg, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) \
    if (g_logger)           \
    g_logger->error(msg, ##__VA_ARGS__)
#define LOG_DEBUG(msg, ...) \
    if (g_logger)           \
    g_logger->debug(msg, ##__VA_ARGS__)
#define LOG_TRACE(msg, ...) \
    if (g_logger)           \
    g_logger->trace(msg, ##__VA_ARGS__)

#elif BUILD_ENV_NAME == teensy41
// Teensy41 environment using Serial
#ifdef ARDUINO
#include <Arduino.h>
#endif

// Initialize serial communication
void init_logger();

// Helper function to format messages for teensy
template <typename... Args>
void serial_log(const char *level, const char *format, Args... args)
{
    Serial.print("[");
    Serial.print(level);
    Serial.print("] ");
    Serial.printf(format, args...);
    Serial.println();
}

// Overload for simple string messages
void serial_log(const char *level, const char *message);

// Logging macros for teensy41 environment
#define LOG_INFO(msg, ...) serial_log("INFO", msg, ##__VA_ARGS__)
#define LOG_WARN(msg, ...) serial_log("WARN", msg, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) serial_log("ERROR", msg, ##__VA_ARGS__)
#define LOG_DEBUG(msg, ...) serial_log("DEBUG", msg, ##__VA_ARGS__)
#define LOG_TRACE(msg, ...) serial_log("TRACE", msg, ##__VA_ARGS__)

#else
// Fallback - no logging
#define LOG_INFO(msg, ...)
#define LOG_WARN(msg, ...)
#define LOG_ERROR(msg, ...)
#define LOG_DEBUG(msg, ...)
#define LOG_TRACE(msg, ...)

void init_logger() {}
#endif

// Common aliases for shorter macro names
#define INFO(msg, ...) LOG_INFO(msg, ##__VA_ARGS__)
#define WARN(msg, ...) LOG_WARN(msg, ##__VA_ARGS__)
#define ERROR(msg, ...) LOG_ERROR(msg, ##__VA_ARGS__)
#define DEBUG(msg, ...) LOG_DEBUG(msg, ##__VA_ARGS__)
#define TRACE(msg, ...) LOG_TRACE(msg, ##__VA_ARGS__)
