#include "Vector3D.h"

Vector3D::Vector3D(){
    v1 = 0; v2 = 0; v3 = 0;
}

Vector3D::Vector3D(float u1, float u2, float u3){
    v1 = u1; v2 = u2; v3 = u3;
}

void Vector3D::normalize(void){
    float mag = sqrt(v1*v1 + v2*v2 + v3*v3);
    v1 = v1/mag; v2 = v2/mag; v3 = v3/mag;
}

String Vector3D::toString(){
    String rtrnStr = "v = < ";
    rtrnStr += String(v1) + ", ";
    rtrnStr += String(v2) + ", ";
    rtrnStr += String(v3) + ", ";
    rtrnStr += ">";
    return rtrnStr;
}