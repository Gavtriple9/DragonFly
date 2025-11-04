#pragma once
#include "dragonfly/sensors/altitude.h"

namespace df
{
    /**
     * @brief Synthetic Barometer driver for testing and simulation.
     *
     * This class simulates a barometer by providing synthetic altitude data.
     * It is useful for testing the system without requiring actual hardware.
     */
    class SyntheticBarometer : public AltitudeSensor
    {
    public:
        /**
         * @brief Constructs a new SyntheticBarometer object.
         */
        SyntheticBarometer() = default;

        /**
         * @brief Destroys the SyntheticBarometer object.
         */
        ~SyntheticBarometer() override = default;

        /**
         * @brief Gets the current altitude from the synthetic barometer.
         *
         * @return float The current altitude.
         */
        float get_altitude() const override;
    };
} // namespace df