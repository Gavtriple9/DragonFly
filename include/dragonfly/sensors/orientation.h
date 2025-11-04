#pragma once
#include "scope/scope.h"

namespace df
{
    /**
     * @brief Abstract base class for Orientation sensors.
     *
     * This class defines the interface for orientation sensors, which are used to
     * determine the orientation of the system in 3D space.
     *
     */
    class OrientationSensor
    {
    public:
        OrientationSensor() = default;
        virtual ~OrientationSensor() = default;

        /**
         * @brief Gets the current orientation from the sensor.
         *
         * @return scope::Quaternion_f The current orientation as a quaternion.
         */
        virtual scope::Quaternion_f get_orientation() const = 0;
    };
}
