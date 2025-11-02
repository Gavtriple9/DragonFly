#pragma once
#include "scope/scope.h"

namespace df
{
    class OrientationSensor
    {
    public:
        OrientationSensor() = default;
        ~OrientationSensor() = default;

        virtual scope::Quaternion_f get_orientation() const = 0;

    private:
        scope::Quaternion_f orientation_;
    };
}
