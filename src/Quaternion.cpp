#include "Quaternion.h"

DF::Quaternion::Quaternion(){
    q0 = 1; q1 = 0; q2 = 0; q3 = 0;
}

DF::Quaternion::Quaternion(float u0, float u1, float u2, float u3){
    q0 = u0; q1 = u1; q2 = u2; q3 = u3;
}

DF::Quaternion::Quaternion(float ang, DF::Vector3D v){
    // axis angle to quaternion conversion
    q0 = cos(ang/2);
    q1 = v.getX()*sin(ang/2);
    q2 = v.getY()*sin(ang/2);
    q3 = v.getZ()*sin(ang/2);
}

DF::Quaternion DF::Quaternion::operator*(DF::Quaternion u){
    // quaternion multiplication
    DF::Vector3D vVect = DF::Vector3D(q1, q2, q3);
    DF::Vector3D uVect = DF::Vector3D(u.q1, u.q2, u.q3);
    DF::Vector3D tempVect = (uVect*q0 + vVect*u.q0 + vVect.cross(uVect));
    return DF::Quaternion(
        q0*u.q0 - vVect.dot(uVect), // q'0
        tempVect.getX(),            // q'1
        tempVect.getY(),            // q'2
        tempVect.getZ()             // q'3
    );
}

DF::Quaternion DF::Quaternion::getInverse(void){
    float mag = q0*q0 + q1*q1 + q2*q2 + q3*q3;
    return DF::Quaternion( q0/mag, -1*q1/mag,-1*q2/mag, -1*q3/mag );
}

String DF::Quaternion::toString(){
    String rtrnStr = "q = < ";
    rtrnStr += String(q0) + ", ";
    rtrnStr += String(q1) + ", ";
    rtrnStr += String(q2) + ", ";
    rtrnStr += String(q3) + ", ";
    rtrnStr += ">";
    return rtrnStr;
}

String DF::Quaternion::toString(int accuracy){
    String rtrnStr = "q = < ";
    rtrnStr += String(q0, accuracy) + ", ";
    rtrnStr += String(q1, accuracy) + ", ";
    rtrnStr += String(q2, accuracy) + ", ";
    rtrnStr += String(q3, accuracy) + ", ";
    rtrnStr += ">";
    return rtrnStr;
}