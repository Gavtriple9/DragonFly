#pragma once
#include "scope/scope.h"
#include "sensors/altitude.h"
#include "sensors/orientation.h"
#include "estimator/ekf.h"

namespace df
{
    class State
    {
    public:
        State() = default;
        ~State() = default;

    private:
        ExtendedKalmanFilter *estimator_;
        AltitudeSensor *altitude_;
        OrientationSensor *orientation_;
        scope::Vector3_f position_;
        scope::Vector3_f velocity_;
        scope::Vector3_f acceleration_;
    };
}
