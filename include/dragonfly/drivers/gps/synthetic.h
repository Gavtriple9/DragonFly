#pragma once
#include "dragonfly/sensors/position.h"

namespace df
{
    /**
     * @brief Synthetic GPS driver for testing and simulation.
     *
     * This class simulates a GPS by providing synthetic position data.
     * It is useful for testing the system without requiring actual hardware.
     */
    class SyntheticGPS : public PositionSensor
    {
    public:
        /**
         * @brief Constructs a new SyntheticGPS object.
         */
        SyntheticGPS() = default;

        /**
         * @brief Destroys the SyntheticGPS object.
         */
        ~SyntheticGPS() override = default;

        /**
         * @brief Gets the current position from the synthetic GPS.
         *
         * @return scope::Vector2_f The current position as a 2D vector.
         */
        scope::Vector2_f get_position() const override;
    };
} // namespace df