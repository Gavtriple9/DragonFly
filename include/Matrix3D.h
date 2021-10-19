#pragma once
#ifndef MATRIX3D_H
#define MATRIX3D_H

#include "Vector3D.h"
#include "Quaternion.h"

namespace DF{
    class Matrix3D {
    public:
        Matrix3D();
        Matrix3D(Quaternion);
        Matrix3D(Vector3D, Vector3D, Vector3D);

        Vector3D getR1(){return r1;};
        Vector3D getR2(){return r2;};
        Vector3D getR3(){return r3;};

        void setR1(Vector3D arg){r1 = arg;};
        void setR2(Vector3D arg){r2 = arg;};
        void setR3(Vector3D arg){r3 = arg;};

        Vector3D operator*(Vector3D v);

        void display();
        float getDet();
        void transpose(void);
        void inverse(void);
        
    private:
        Vector3D r1;
        Vector3D r2;
        Vector3D r3;
    };
}
#endif
