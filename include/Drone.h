#pragma once
#ifndef DRONE_H
#define DRONE_H

#include "Core.h"

#include <I2Cdev.h>
#include <MPU6050.h>
#include <SFE_BMP180.h>
#include <TinyGPS++.h>

#include "Quaternion.h"

#define CALIBRATION_PASSES 15

namespace DF {
    class Drone {
    public:
        Drone();
        void initialize(void);
        void calibrateIMU(void);
        bool testConnections();

    private:
        MPU6050 imu;	        // inertial measurement unit 
        SFE_BMP180 pressure; 	// barametric pressure sensor
        TinyGPSPlus gps;        // possible gps library
        
        Vector3D pos;
        Vector3D vel;
        Vector3D acc;
        Quaternion orientation;
        Quaternion omega;
    };
}

#endif