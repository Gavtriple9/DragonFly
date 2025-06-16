#include "quaternion.hpp"
#include <cmath>
#include <stdexcept>

namespace df_math
{
    Quaternion &Quaternion::operator=(const Quaternion &other)
    {
        if (this != &other) // Check for self-assignment
        {
            w = other.w;
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    Quaternion Quaternion::operator+(const Quaternion &other) const
    {
        return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
    }

    Quaternion Quaternion::operator-(const Quaternion &other) const
    {
        return Quaternion(w - other.w, x - other.x, y - other.y, z - other.z);
    }

    Quaternion Quaternion::operator*(const Quaternion &other) const
    {
        return Quaternion(
            w * other.w - x * other.x - y * other.y - z * other.z,
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.x,
            w * other.z + x * other.y - y * other.x + z * other.w);
    }

    Quaternion Quaternion::operator*(float scalar) const
    {
        return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
    }

    Quaternion Quaternion::operator/(float scalar) const
    {
        if (scalar == 0.0f)
        {
            throw std::invalid_argument("Division by zero in quaternion division");
        }
        return Quaternion(w / scalar, x / scalar, y / scalar, z / scalar);
    }

    Quaternion Quaternion::conjugate() const
    {
        return Quaternion(w, -x, -y, -z);
    }

    float Quaternion::norm() const
    {
        return sqrt(w * w + x * x + y * y + z * z);
    }

    Quaternion Quaternion::normalized() const
    {
        float n = norm();
        if (n == 0.0f)
        {
            throw std::invalid_argument("Cannot normalize a zero quaternion");
        }
        return *this / n;
    }

    Quaternion Quaternion::inverse() const
    {
        float n = norm();
        if (n == 0.0f)
        {
            throw std::invalid_argument("Cannot compute inverse of a zero quaternion");
        }
        return conjugate() / (n * n);
    }

    Quaternion Quaternion::fromAxisAngle(float angle, float x, float y, float z)
    {
        float half_angle = angle * 0.5f;
        float s = sin(half_angle);
        return Quaternion(cos(half_angle), x * s, y * s, z * s).normalized();
    }

    Quaternion Quaternion::fromEuler(float roll, float pitch, float yaw)
    {
        float cy = cos(yaw * 0.5f);
        float sy = sin(yaw * 0.5f);
        float cp = cos(pitch * 0.5f);
        float sp = sin(pitch * 0.5f);
        float cr = cos(roll * 0.5f);
        float sr = sin(roll * 0.5f);

        return Quaternion(
                   cr * cp * cy + sr * sp * sy,
                   sr * cp * cy - cr * sp * sy,
                   cr * sp * cy + sr * cp * sy,
                   cr * cp * sy - sr * sp * cy)
            .normalized();
    }
};
