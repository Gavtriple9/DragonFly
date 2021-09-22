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

DF::Vector3D DF::Matrix3D::operator*(DF::Vector3D v){
    float newX = xComp.getX() * v.getX() + xComp.getY() * v.getY() + xComp.getZ() * v.getZ();
    float newY = yComp.getX() * v.getX() + yComp.getY() * v.getY() + yComp.getZ() * v.getZ();
    float newZ = zComp.getX() * v.getX() + zComp.getY() * v.getY() + zComp.getZ() * v.getZ();
    
    return DF::Vector3D(newX, newY, newZ);
}

void DF::Matrix3D::display(){
    for ( int i = 0; i < 3; i++ ){
       Serial.println();
    }  
}