#include "PID.h"

PID::PID(float a, float b, float c){
    kP = a;
    kI = b;
    kD = c;
}

float PID::loop(float measuredVal, float setPoint, float dt){
    error = setPoint - measuredVal;
    integral = integral + error * dt;
    float derivative = (error - prevError) / dt;
    prevError = error;
    return kP * error + kI * integral + kD * derivative;
}