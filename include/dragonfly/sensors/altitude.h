#pragma once

namespace df
{
    class AltitudeSensor
    {
    public:
        AltitudeSensor() = default;
        ~AltitudeSensor() = default;

        virtual float get_altitude() const = 0;
    };
}
