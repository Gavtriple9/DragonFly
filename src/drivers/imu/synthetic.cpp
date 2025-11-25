#include <dragonfly/drivers/imu/synthetic.h>
#include <random>
#include <dragonfly/logging.h>

// Generate AWGN noise for quaternion components
std::random_device rd;
std::mt19937 gen(rd());
std::normal_distribution<float> noise(0.0f, 0.01f); // Mean=0, StdDev=0.01

scope::Quaternion_f df::SyntheticIMU::get_orientation() const
{

    // Create base quaternion (identity or your desired orientation)
    scope::Quaternion_f q(1.0f, 0.0f, 0.0f, 0.0f);

    // Add noise to quaternion components
    q.w += noise(gen);
    q.x += noise(gen);
    q.y += noise(gen);
    q.z += noise(gen);

    // Normalize to maintain unit quaternion constraint
    q.normalize();

    return q;
}
