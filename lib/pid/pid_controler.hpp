namespace df
{
    class PIDController
    {
    public:
        PIDController(double kp, double ki, double kd)
            : kp_(kp), ki_(ki), kd_(kd), previous_error_(0.0), integral_(0.0) {}

        double compute(double setpoint, double measured_value, double dt);

    private:
        double kp_;             // Proportional gain
        double ki_;             // Integral gain
        double kd_;             // Derivative gain
        double previous_error_; // Previous error for derivative calculation
        double integral_;       // Integral of error for integral calculation
    };
}
