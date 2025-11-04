#pragma once
#include "dragonfly/sensors/arm.h"

namespace df
{
    /**
     * @brief Synthetic Input driver for testing and simulation.
     *
     * This class simulates an Input device by providing synthetic orientation data.
     * It is useful for testing the system without requiring actual hardware.
     */
    class SyntheticInput : public ArmSensor
    {
    public:
        /**
         * @brief Constructs a new SyntheticInput object.
         */
        SyntheticInput() = default;

        /**
         * @brief Destroys the SyntheticInput object.
         */
        ~SyntheticInput() override = default;

        /**
         * @brief Checks if the system is armed.
         *
         * @return true if the system is armed, false otherwise.
         */
        bool is_armed() const override;
    };
} // namespace df