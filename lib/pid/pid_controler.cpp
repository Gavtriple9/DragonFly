#include "pid_controler.hpp"

namespace df
{
    double PIDController::compute(double setpoint, double measured_value, double dt)
    {
        double error = setpoint - measured_value;
        integral_ += error * dt;
        double derivative = (error - previous_error_) / dt;

        double output = kp_ * error + ki_ * integral_ + kd_ * derivative;

        previous_error_ = error;
        return output;
    }
} // namespace df
