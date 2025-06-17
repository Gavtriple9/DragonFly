#include <gtest/gtest.h>
#include "../../lib/math/quaternion.hpp"

using namespace df;

// Test basic quaternion construction
TEST(QuaternionTest, DefaultConstructor)
{
    Quaternion q;
    EXPECT_FLOAT_EQ(q.w, 1.0f);
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
}

TEST(QuaternionTest, ParameterizedConstructor)
{
    Quaternion q(0.5f, 0.5f, 0.5f, 0.5f);
    EXPECT_FLOAT_EQ(q.w, 0.5f);
    EXPECT_FLOAT_EQ(q.x, 0.5f);
    EXPECT_FLOAT_EQ(q.y, 0.5f);
    EXPECT_FLOAT_EQ(q.z, 0.5f);
}

TEST(QuaternionTest, CopyConstructor)
{
    Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    Quaternion q2(q1);
    EXPECT_FLOAT_EQ(q2.w, 1.0f);
    EXPECT_FLOAT_EQ(q2.x, 2.0f);
    EXPECT_FLOAT_EQ(q2.y, 3.0f);
    EXPECT_FLOAT_EQ(q2.z, 4.0f);
}

// Test quaternion operations
TEST(QuaternionTest, Addition)
{
    Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    Quaternion q2(0.5f, 1.5f, 2.5f, 3.5f);
    Quaternion result = q1 + q2;

    EXPECT_FLOAT_EQ(result.w, 1.5f);
    EXPECT_FLOAT_EQ(result.x, 3.5f);
    EXPECT_FLOAT_EQ(result.y, 5.5f);
    EXPECT_FLOAT_EQ(result.z, 7.5f);
}

TEST(QuaternionTest, Subtraction)
{
    Quaternion q1(2.0f, 3.0f, 4.0f, 5.0f);
    Quaternion q2(1.0f, 1.0f, 2.0f, 2.0f);
    Quaternion result = q1 - q2;

    EXPECT_FLOAT_EQ(result.w, 1.0f);
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 2.0f);
    EXPECT_FLOAT_EQ(result.z, 3.0f);
}

TEST(QuaternionTest, ScalarMultiplication)
{
    Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    Quaternion result = q * 2.0f;

    EXPECT_FLOAT_EQ(result.w, 2.0f);
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
    EXPECT_FLOAT_EQ(result.z, 8.0f);
}

TEST(QuaternionTest, ScalarDivision)
{
    Quaternion q(2.0f, 4.0f, 6.0f, 8.0f);
    Quaternion result = q / 2.0f;

    EXPECT_FLOAT_EQ(result.w, 1.0f);
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 3.0f);
    EXPECT_FLOAT_EQ(result.z, 4.0f);
}

TEST(QuaternionTest, Conjugate)
{
    Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    Quaternion conj = q.conjugate();

    EXPECT_FLOAT_EQ(conj.w, 1.0f);
    EXPECT_FLOAT_EQ(conj.x, -2.0f);
    EXPECT_FLOAT_EQ(conj.y, -3.0f);
    EXPECT_FLOAT_EQ(conj.z, -4.0f);
}

TEST(QuaternionTest, Norm)
{
    Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    float norm = q.norm();
    float expected = sqrt(30.0f);
    EXPECT_FLOAT_EQ(norm, expected);
}

TEST(QuaternionTest, UnitQuaternionNorm)
{
    Quaternion q; // Default constructor creates unit quaternion
    EXPECT_FLOAT_EQ(q.norm(), 1.0f);
}

TEST(QuaternionTest, Normalized)
{
    Quaternion q(2.0f, 0.0f, 0.0f, 0.0f);
    Quaternion normalized = q.normalized();

    EXPECT_FLOAT_EQ(normalized.w, 1.0f);
    EXPECT_FLOAT_EQ(normalized.x, 0.0f);
    EXPECT_FLOAT_EQ(normalized.y, 0.0f);
    EXPECT_FLOAT_EQ(normalized.z, 0.0f);
    EXPECT_FLOAT_EQ(normalized.norm(), 1.0f);
}

TEST(QuaternionTest, OrthogonalQuaternionMultiplication)
{
    Quaternion q1(1.0f, 0.0f, 0.0f, 0.0f); // Real quaternion
    Quaternion q2(0.0f, 1.0f, 0.0f, 0.0f); // Pure imaginary i
    Quaternion result = q1 * q2;

    EXPECT_FLOAT_EQ(result.w, 0.0f);
    EXPECT_FLOAT_EQ(result.x, 1.0f);
    EXPECT_FLOAT_EQ(result.y, 0.0f);
    EXPECT_FLOAT_EQ(result.z, 0.0f);
}

TEST(QuaternionTest, ArbitraryQuaternionMultiplication)
{
    Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    Quaternion q2(5.0f, 6.0f, 7.0f, 8.0f);
    Quaternion result = q1 * q2;

    EXPECT_FLOAT_EQ(result.w, -60.0f);
    EXPECT_FLOAT_EQ(result.x, 12.0f);
    EXPECT_FLOAT_EQ(result.y, 30.0f);
    EXPECT_FLOAT_EQ(result.z, 24.0f);
}

TEST(QuaternionTest, AxisAngleConstruction)
{
    // 90 degree rotation around z-axis
    float angle = M_PI / 2.0f;
    Quaternion q = Quaternion::fromAxisAngle(angle, 0.0f, 0.0f, 1.0f);

    EXPECT_NEAR(q.w, cos(angle / 2.0f), 1e-6f);
    EXPECT_NEAR(q.x, 0.0f, 1e-6f);
    EXPECT_NEAR(q.y, 0.0f, 1e-6f);
    EXPECT_NEAR(q.z, sin(angle / 2.0f), 1e-6f);
    EXPECT_NEAR(q.norm(), 1.0f, 1e-6f);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
