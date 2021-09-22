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

        Vector3D getX(){return xComp;};
        Vector3D getY(){return yComp;};
        Vector3D getZ(){return zComp;};

        void setX(Vector3D arg){xComp = arg;};
        void setY(Vector3D arg){yComp = arg;};
        void setZ(Vector3D arg){zComp = arg;};

        Vector3D operator*(Vector3D v);

        void display();
        
    private:
        Vector3D xComp;
        Vector3D yComp;
        Vector3D zComp;
    };
}
#endif