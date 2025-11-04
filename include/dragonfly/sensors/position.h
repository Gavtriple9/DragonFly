#pragma once
#include "scope/scope.h"

namespace df
{
    /**
     * @brief Abstract base class for Position sensors.
     *
     * This class defines the interface for position sensors, which are used to
     * determine the position of the system in 2D space.
     */
    class PositionSensor
    {
    public:
        PositionSensor() = default;
        virtual ~PositionSensor() = default;

        /**
         * @brief Gets the current position from the sensor.
         *
         * @return scope::Vector2_f The current position as a 2D vector.
         */
        virtual scope::Vector2_f get_position() const = 0;
    };
}
