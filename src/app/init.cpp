#include <config.h>
#include "init.hpp"
#include "../hal/hal_gpio.hpp"

#if BUILD_ENV_NAME == native_env
#include <thread>
#include <chrono>
#include <iostream>
#include <filesystem>
#endif

// Define static member variable
#if BUILD_ENV_NAME == teensy41
usb_serial_class df::Application::logger;
#elif BUILD_ENV_NAME == native_env
std::shared_ptr<spdlog::logger> df::Application::logger;
#endif

df::State df::Application::state;

// ------------------------------ Public methods ----------------------------- //

void df::Application::init()
{
    setup_logging();
    setup_hardware();
}

void df::Application::main_loop()
{
    for (int i = 0;; i++)
    {
        // Log iteration
#if BUILD_ENV_NAME == native_env
        logger->info("Loop iteration: {}", i);
#else
        logger.printf("Loop iteration: %d\n", i);
#endif

        // Every 10 iterations, demonstrate toggle
        if (i % 10 == 9)
        {
#if BUILD_ENV_NAME == native_env
            logger->info("Demonstrating toggle functionality:");
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
#else
            logger.println("Demonstrating toggle functionality:");
            for (int j = 0; j < 3; j++)
            {
                delay(100);
            }
#endif
        }
    }
}

// ------------------------------ Private methods ---------------------------- //

void df::Application::setup_hardware()
{
}

void df::Application::setup_logging()
{
#if BUILD_ENV_NAME == native_env
    // Create logs directory if it doesn't exist
    std::filesystem::create_directories("logs");

    // Create console logger with color support
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);

    // Create file logger
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/dragonfly.log", true);
    file_sink->set_level(spdlog::level::trace);

    // Combine both sinks
    std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
    logger = std::make_shared<spdlog::logger>("dragonfly", sinks.begin(), sinks.end());

    // Set logger level and pattern
    logger->set_level(spdlog::level::trace);
    logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v");

    // Register logger globally
    spdlog::register_logger(logger);
    spdlog::set_default_logger(logger);

    logger->info("spdlog initialized for native build");
#else
    logger = Serial;
    logger.begin(BAUD_RATE);
    while (!this->logger)
    {
    }
#endif
}
// ---------------------------------------------------------------------------- //
