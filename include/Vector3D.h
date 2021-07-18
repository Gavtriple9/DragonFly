#pragma once
#ifndef Vector3D_H
#define Vector3D_H

#include "Core.h"

// Typical vector class
namespace DF{
    class Vector3D {
    public:
        // class initializer overloads
        Vector3D();
        Vector3D(float u1, float u2, float u3);
        void normalize(void); // normalizes self
        Vector3D getNorm(void); // returns a unit vector in the same direction as self
        String toString();
        String toString(int accuracy);

        Vector3D cross(Vector3D);
        float dot(Vector3D);

        Vector3D operator*(float);
        Vector3D operator+(Vector3D);

        // get methods
        float getX(){return v1;};
        float getY(){return v2;};
        float getZ(){return v3;};

        // set methods
        void setX(float t){v1 = t;};
        void setY(float t){v2 = t;};
        void setZ(float t){v3 = t;};

    private:
        float v1, v2, v3; // x, y, z
    };
}
#endif