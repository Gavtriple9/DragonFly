#pragma once
#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3D.h"
#include "Core.h"

class Quaternion {
public:
    Quaternion(void);
    Quaternion(float ang, Vector3D v);
    Quaternion(float q0, float q1, float q2, float q3);

    String toString();
private:
    float q0, q1, q2, q3;
};

#endif