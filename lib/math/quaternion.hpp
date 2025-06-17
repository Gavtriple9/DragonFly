namespace df
{
    /**
     * @brief Quaternion class for representing and manipulating quaternions.
     *
     *  This class provides methods for quaternion arithmetic, including addition,
     *  subtraction, multiplication, division, conjugation, normalization, and conversion
     *  from axis-angle and Euler angles. Quaternions are used in 3D graphics and physics
     *  for representing rotations and orientations in a compact and efficient manner.
     *
     */
    class Quaternion
    {
    public:
        float w, x, y, z;

        Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
        Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}
        Quaternion(const Quaternion &other) : w(other.w), x(other.x), y(other.y), z(other.z) {}

        ~Quaternion() = default;

        static Quaternion fromAxisAngle(float angle, float x, float y, float z);
        static Quaternion fromEuler(float roll, float pitch, float yaw);

        Quaternion &operator=(const Quaternion &other);
        Quaternion operator+(const Quaternion &other) const;
        Quaternion operator-(const Quaternion &other) const;
        Quaternion operator*(const Quaternion &other) const;
        Quaternion operator*(float scalar) const;
        Quaternion operator/(float scalar) const;

        Quaternion conjugate() const;
        float norm() const;
        Quaternion normalized() const;
        Quaternion inverse() const;
    };
}