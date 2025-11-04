#pragma once
#include "dragonfly/sensors/orientation.h"

namespace df
{
    /**
     * @brief Synthetic IMU driver for testing and simulation.
     *
     * This class simulates an Inertial Measurement Unit (IMU) by providing
     * synthetic orientation data. It is useful for testing the system without
     * requiring actual hardware.
     */
    class SyntheticIMU : public OrientationSensor
    {
    public:
        /**
         * @brief Constructs a new SyntheticIMU object.
         */
        SyntheticIMU() = default;

        /**
         * @brief Destroys the SyntheticIMU object.
         */
        ~SyntheticIMU() override = default;

        /**
         * @brief Gets the current orientation from the synthetic IMU.
         *
         * @return scope::Quaternion_f The current orientation as a quaternion.
         */
        scope::Quaternion_f get_orientation() const override;
    };
} // namespace df