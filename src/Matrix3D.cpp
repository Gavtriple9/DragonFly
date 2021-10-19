#include "Matrix3D.h"

// default constructor
DF::Matrix3D::Matrix3D(){
    r1 = Vector3D(0,0,0);
    r2 = Vector3D(0,0,0);
    r3 = Vector3D(0,0,0);
}

// constructs matrix from quaternion
DF::Matrix3D::Matrix3D(Quaternion q){
    float qXSquared = q.getX() * q.getX();
    float qYSquared = q.getY() * q.getY();
    float qZSquared = q.getZ() * q.getZ();

    float qXqY = q.getX() * q.getY();
    float qXqZ = q.getX() * q.getZ();
    float qXqW = q.getX() * q.getW();
    float qYqZ = q.getY() * q.getZ();
    float qYqW = q.getY() * q.getW();
    float qZqW = q.getZ() * q.getW();

    r1 = Vector3D(1-2*(qYSquared + qZSquared), 2*(qXqY - qZqW), 2*(qXqZ + qYqW));
    r2 = Vector3D(2*(qXqY + qZqW), 1-2*(qXSquared + qZSquared), 2*(qYqZ - qXqW));
    r3 = Vector3D(2*(qXqZ - qYqW), 2*(qYqZ + qXqW), 1-2*(qXSquared + qYSquared));
}

// constructs matrix from row vectors
DF::Matrix3D::Matrix3D(Vector3D v1, Vector3D v2, Vector3D v3 ){
    r1 = v1;
    r2 = v2;
    r3 = v3;
}

// matrix multiplication of a vector
DF::Vector3D DF::Matrix3D::operator*(DF::Vector3D v){
    float newX = r1.getX() * v.getX() + r1.getY() * v.getY() + r1.getZ() * v.getZ();
    float newY = r2.getX() * v.getX() + r2.getY() * v.getY() + r2.getZ() * v.getZ();
    float newZ = r3.getX() * v.getX() + r3.getY() * v.getY() + r3.getZ() * v.getZ();
    
    return DF::Vector3D(newX, newY, newZ);
}
// prints the matrix to the console
void DF::Matrix3D::display(){
    for ( int i = 0; i < 3; i++ ){
       Serial.println();
    }  
}

// returns determinate of matrix
float DF::Matrix3D::getDet(){
    float compX = r1.getX()*(r2.getY() * r3.getZ() - r2.getZ() * r3.getY());
    float compY = r1.getY()*(r2.getZ() * r3.getX() - r2.getX() * r3.getZ());
    float compZ = r1.getZ()*(r2.getX() * r3.getY() - r2.getY() * r3.getX());
    return compX + compY + compZ;
}

// transposes current matrix
void DF::Matrix3D::transpose(){
    r1 = DF::Vector3D(r1.getX(), r2.getX(), r3.getX());
    r2 = DF::Vector3D(r1.getY(), r2.getY(), r3.getY());
    r3 = DF::Vector3D(r1.getZ(), r2.getZ(), r3.getZ());
}

void DF::Matrix3D::inverse(){
    float detM = getDet();
    if ( detM == 0 ){
        Serial.println("Error: Matrix not invertible, Det = 0");
    } else if ( detM == 1 ){
        transpose();
    } else {
        float Ma = r1.getX();
        float Mb = r1.getY();
        float Mc = r1.getZ();
        float Md = r2.getX();
        float Mf = r2.getY();
        float Mg = r2.getZ();
        float Mh = r3.getX();
        float Mj = r3.getY();
        float Mk = r3.getZ();

        r1 = Vector3D( Mf*Mk-Mg*Mj, Mc*Mj-Mb*Mk, Mb*Mg-Mc*Mf )*(1/detM);
        r2 = Vector3D( Mg*Mh-Md*Mk, Ma*Mk-Mc*Mh, Mc*Md-Ma*Mg )*(1/detM);
        r3 = Vector3D( Md*Mj-Mf*Mh, Mb*Mh-Ma*Mj, Ma*Mf-Mb*Md )*(1/detM);
    }

}
