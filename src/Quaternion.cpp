#include "Quaternion.h"

Quaternion::Quaternion(){
    q0 = 1; q1 = 0; q2 = 0; q3 = 0;
}

Quaternion::Quaternion(float ang, Vector3D v){
    q0 = cos(ang/2);
    q1 = v.getX()*sin(ang/2);
    q2 = v.getY()*sin(ang/2);
    q3 = v.getZ()*sin(ang/2);
}

String Quaternion::toString(){
    String rtrnStr = "q = < ";
    rtrnStr += String(q0) + ", ";
    rtrnStr += String(q1) + ", ";
    rtrnStr += String(q2) + ", ";
    rtrnStr += String(q3) + ", ";
    rtrnStr += ">";
    return rtrnStr;
}