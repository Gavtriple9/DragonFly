#pragma once

#ifndef PID_h
#define PID_h
#include "Core.h"

class PID {
private:
    float kP, kI, kD;
    float error, prevError;
    float integral;

public:
    PID(){};
    PID(float a, float b, float c);

    float getKP(void);
    float getKI(void);
    float getKD(void);

    void setKP(float);
    void setKI(float);
    void setKD(float);

    float loop(float measuredVal, float setPoint, float dt);
};
#endif