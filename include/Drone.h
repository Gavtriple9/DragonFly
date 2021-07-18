#pragma once
#include "Core.h"
#ifndef DRONE_H
#define DRONE_H

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

    };
}

#endif