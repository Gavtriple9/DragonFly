#pragma once
#ifndef QUATERNION_H
#define QUATERNION_H

#include "Core.h"

#include "Vector3D.h"

namespace DF{
    class Quaternion {
    public:
        Quaternion(void);
        Quaternion(float ang, Vector3D v);
        Quaternion(float q0, float q1, float q2, float q3);

        String toString(void);
        String toString(int accuracy);

        Quaternion operator*(Quaternion u);
        Quaternion getInverse(void);

    private:
        float q0, q1, q2, q3;
    };
}
#endif