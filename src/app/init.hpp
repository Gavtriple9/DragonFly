#pragma once

#ifndef BUILD_ENV_NAME
#error "Add -D BUILD_ENV_NAME=$PIOENV to platformio.ini build_flags"
#else
#define native_env 100
#define teensy41 101
#endif

#if BUILD_ENV_NAME == native_env
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>
#else
#include <Arduino.h>
#endif

#include "app/state.hpp"

namespace df
{
    /**
     * @brief The main application class for the Dragonfly project.
     *
     * This class is responsible for initializing the application and running the main loop.
     */
    class Application
    {
    public:
        /**
         * @brief Initializes the application.
         *
         *  This function sets up the subsystems required for the application to run,
         */
        void init();

        /**
         * @brief Runs the main loop of the application.
         *
         *   This function contains the main logic of the application and runs indefinitely.
         *   It is a blocking call, meaning it will not return until the application is terminated.
         */
        void main_loop();

    private:
#if BUILD_ENV_NAME == teensy41
        static usb_serial_class logger;
#elif BUILD_ENV_NAME == native_env
        static std::shared_ptr<spdlog::logger> logger;
#endif
        static State state;
        /**
         * @brief
         *
         *  This function sets up the serial communication for logging purposes.
         */
        void setup_logging();

        /**
         * @brief Setup the connected hardware.
         *
         *  This function is a placeholder for hardware initialization logic.
         *  Currently, it does not perform any operations.
         */
        void setup_hardware();
    };
}
