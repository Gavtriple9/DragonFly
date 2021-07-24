#pragma once
#ifndef DRONE_H
#define DRONE_H

#include "Core.h"

#include <I2Cdev.h>
#include <MPU6050.h>
#include <MadgwickAHRS.h>
#include <SFE_BMP180.h>
#include <TinyGPS++.h>

#include "Quaternion.h"

#define CALIBRATION_LOOPS 15


namespace DF {
    class Drone {
    public:

        static const int RXPin = 0, TXPin = 1;
        static const uint32_t GPSBaud = 9600;

        Drone();
        void initialize(void);
        void calibrateIMU(void);
        bool testConnections();

        void update();
        void updateGPS(int);
        String strStatus();

    private:
        MPU6050 imu;	        // inertial measurement unit 
        SFE_BMP180 pressure; 	// barametric pressure sensor
        TinyGPSPlus gps;        // possible gps library
        Madgwick filter;        // calculates current quaternion

        struct{
            Vector3D pos;
            Vector3D vel;
            Vector3D acc;
            Quaternion orientation;
            Quaternion omega;
        }state;

        void getData();
    };
}

#endif