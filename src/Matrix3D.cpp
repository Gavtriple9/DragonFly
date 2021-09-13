#include "Matrix3D.h"

DF::Matrix3D::Matrix3D(){
    xComp = Vector3D(0,0,0);
    xComp = Vector3D(0,0,0);
    xComp = Vector3D(0,0,0);
}

DF::Matrix3D::Matrix3D(Quaternion q){
    float qYSquared = q.getY() * q.getY();
    float qXSquared = q.getX() * q.getX();
    float qZSquared = q.getZ() * q.getZ();

    float qXqY = q.getX()*q.getY();
    float qXqZ = q.getX()*q.getZ();
    float qXqW = q.getX()*q.getW();
    float qYqZ = q.getY()*q.getZ();
    float qYqW = q.getY()*q.getW();
    float qZqW = q.getZ()*q.getW();


    xComp = Vector3D(1-2*(qYSquared + qZSquared), 2*(qXqY - qZqW), 2*(qXqZ + qYqW));
    yComp = Vector3D(2*(qXqY + qZqW), 1-2*(qXSquared + qZSquared), 2*(qYqZ - qXqW));
    zComp = Vector3D(2*(qXqZ - qYqW), 2*(qYqZ + qXqW), 1-2*(qXSquared + qYSquared));
}