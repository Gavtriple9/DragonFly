#pragma once

#include <optional>
#include <memory>
#include "scope/scope.h"

#include "sensors/altitude.h"
#include "sensors/orientation.h"
#include "sensors/arm.h"

#include "drivers/barometer/synthetic.h"
#include "drivers/gps/synthetic.h"
#include "drivers/imu/synthetic.h"
#include "drivers/input/synthetic.h"

namespace df
{
    /**
     * @brief The main application class for the Dragonfly project.
     *
     * This class is responsible for initializing the application and running the main loop.
     */
    class Dragonfly
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
        // Sensors
        std::unique_ptr<OrientationSensor> orientation_sensor_;
        std::optional<std::unique_ptr<AltitudeSensor>> altitude_sensor_;
        std::unique_ptr<ArmSensor> arm_sensor_;

        // State
        // Translational state
        scope::Vector3_f position_;
        scope::Vector3_f velocity_;
        scope::Vector3_f acceleration_;

        // Rotational state
        scope::Quaternion_f orientation_;
        scope::Quaternion_f angular_velocity_;
        scope::Quaternion_f angular_acceleration_;

        /**
         * @brief Sets up the logging subsystem.
         *
         *  This function sets up the serial communication for logging purposes.
         */
        void setup_logging();

        /**
         * @brief Setup the connected sensors.
         *
         * Sensors initialization logic.
         */
        void setup_sensors();
    };
}
