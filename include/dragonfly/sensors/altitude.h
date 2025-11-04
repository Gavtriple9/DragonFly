#pragma once

namespace df
{
    /**
     * @brief Abstract base class for Altitude sensors.
     *
     * This class defines the interface for altitude sensors, which are used to
     * measure the altitude of the system.
     */
    class AltitudeSensor
    {
    public:
        AltitudeSensor() = default;
        virtual ~AltitudeSensor() = default;

        /**
         * @brief Gets the current altitude from the sensor.
         *
         * @return float The current altitude.
         */
        virtual float get_altitude() const = 0;
    };
}
