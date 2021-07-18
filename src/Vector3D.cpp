#include "Vector3D.h"

DF::Vector3D::Vector3D(){
    v1 = 0; v2 = 0; v3 = 0;
}

DF::Vector3D::Vector3D(float u1, float u2, float u3){
    v1 = u1; v2 = u2; v3 = u3;
}

float DF::Vector3D::dot(DF::Vector3D u){
    return v1*u.v1 + v2*u.v2 + v3*u.v3;
}

DF::Vector3D DF::Vector3D::cross(DF::Vector3D u){
    return DF::Vector3D(
        v2*u.v3-v3*u.v2, // i
        v3*u.v1-v1*u.v3, // j
        v1*u.v2-v2*u.v1  // k
    );
}

DF::Vector3D DF::Vector3D::operator*(float scalar){
    return DF::Vector3D(scalar*v1, scalar*v2, scalar*v3);
}

DF::Vector3D DF::Vector3D::operator+(DF::Vector3D u){
    return DF::Vector3D(v1+u.v1, v2+u.v2, v3+u.v3);
}

void DF::Vector3D::normalize(void){
    float mag = sqrt(v1*v1 + v2*v2 + v3*v3);
    v1 = v1/mag; v2 = v2/mag; v3 = v3/mag;
}


DF::Vector3D DF::Vector3D::getNorm(void){
    float mag = sqrt(v1*v1 + v2*v2 + v3*v3);
    return DF::Vector3D(v1/mag, v2/mag, v3/mag);
}


String DF::Vector3D::toString(){
    String rtrnStr = "v = < ";
    rtrnStr += String(v1) + ", ";
    rtrnStr += String(v2) + ", ";
    rtrnStr += String(v3) + ", ";
    rtrnStr += ">";
    return rtrnStr;
}

String DF::Vector3D::toString(int accuracy){
    String rtrnStr = "v = < ";
    rtrnStr += String(v1, accuracy) + ", ";
    rtrnStr += String(v2, accuracy) + ", ";
    rtrnStr += String(v3, accuracy) + ", ";
    rtrnStr += ">";
    return rtrnStr;
}