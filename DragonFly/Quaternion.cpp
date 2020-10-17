#include "Quaternion.h"

Quaternion::Quaternion(){ xComp = 0; yComp = 0; zComp = 0; wComp = 0; }

Quaternion::Quaternion( float arg4, float arg1, float arg2, float arg3 ){ xComp = arg1; yComp = arg2; zComp = arg3; wComp = arg4; }

void Quaternion::normalize(void){ 
    float magnitude = Quaternion::getMag(); 
    xComp /= magnitude;
    yComp /= magnitude;
    zComp /= magnitude;
    wComp /= magnitude;
}

float Quaternion::operator *( Quaternion Q2 ){
    return( getx()*Q2.getx() + gety()*Q2.gety() + getz()*Q2.getz() );
}
Quaternion Quaternion::operator &( Quaternion Q2 ){
    return Quaternion( 0, gety()*Q2.getz() - getz()*Q2.gety(), getz()*Q2.getx() - getx()*Q2.getz(), getx()*Q2.gety() - gety()*Q2.getx() );
}

float Quaternion::getAngle(void){
    setAngle(2*atan2(sqrt( xComp*xComp + yComp*yComp + zComp*zComp ), getw()));
    return (angle);
}

float Quaternion::getMag(void){
    return sqrt( xComp*xComp + yComp*yComp + zComp*zComp + wComp*wComp );
}

void Quaternion::report(void){
    Serial.println( "Quat: < " + String(getw(),4) + ", " + String(getx(),4) + ", " + String(gety(),4) + ", " + String(getz(),4) + " >" );
}
