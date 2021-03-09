#pragma once

#include "Core.h"

#ifndef BMP180_h
#define BMP180_h

#define BMP180_ADDRESS 0x77



class BMP180 {
public:
    BMP180(uint i);
    BMP180(){};
    void initialize(void);
    void getValues(float *T, float* P, float* A);

private:
    const unsigned char OSS;

    // calibration parameters
    short int ac1_m;
    short int ac2_m;
    short int ac3_m;
    unsigned short int ac4_m;
    unsigned short int ac5_m;
    unsigned short int ac6_m;
    short int b1_m;
    short int b2_m;
    short int mb_m;
    short int mc_m;
    short int md_m;

    long b5_m;

    // gather and manipulate variables
    unsigned int readUT(void);
    unsigned long readUP(void);
    int readInt(unsigned char address);
    char read(unsigned char address);
    long getPressure(unsigned long up);
    float getTemperature(unsigned int ut);
    float calcAltitude(float pressure);
};

#endif
