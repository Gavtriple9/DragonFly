#pragma once

namespace df
{
    /**
     * @brief Abstract base class for Arm sensors.
     *
     * This class defines the interface for arm sensors, which are used to
     * determine whether a system is armed or disarmed.
     */
    class ArmSensor
    {
    public:
        ArmSensor() = default;
        virtual ~ArmSensor() = default;

        /**
         * @brief Checks if the system is armed.
         *
         * @return true if the system is armed, false otherwise.
         */
        virtual bool is_armed() const = 0;
    };
}
