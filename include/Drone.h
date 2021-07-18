#pragma once
#ifndef DRONE_H
#define DRONE_H

#include "Core.h"

#include "I2Cdev.h"
#include "MPU6050.h"
#include "TinyGPS++.h"

namespace DF {
    class Drone {
    public:
        Drone();
        void initialize(void);
        void calibrateIMU(void);

    private:
    // Sensors ///////////////////////////////////////////
        MPU6050 imu;	    // inertial measurement unit 
        // BMP180 bmp; 	    // barametric pressure sensor
        TinyGPSPlus gps;    // possible gps library
    /////////////////////////////////////////////////////
    float pos;
    float vel;
    float acc;
    float orientation;
    float omega;

    };
}

#endif