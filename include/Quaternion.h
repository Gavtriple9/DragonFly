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

        float getW(){return q0;};
        float getX(){return q1;};
        float getY(){return q2;};
        float getZ(){return q3;};

    private:
        float q0, q1, q2, q3; // w, x, y, z
    };
}
#endif