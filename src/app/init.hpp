#pragma once

#include <dragonfly/environment.h>
#include <dragonfly/logging.h>
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
