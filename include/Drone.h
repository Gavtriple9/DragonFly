#pragma once
#ifndef DRONE_H
#define DRONE_H

#include "Core.h"

#include <I2Cdev.h>
#include <Servo.h>
#include <MPU6050.h>
#include <PPMReader.h>
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
        // Drone functions
        void initialize(void);
        void calibrateIMU(void);
        void getUserCommand(void);
        bool testConnections(); // TODO: Add other sensors

        void updateReadings();
        void updateGPS(int);
        String strStatus();

        // Motor control functions
        void setMotor1Speed(float);
        void setMotor2Speed(float);
        void setMotor3Speed(float);
        void setMotor4Speed(float);
        void setAllMotors(float);

        void calibrateMotors(void);
        
        // Controller collected data
        void updateReciever(void);
        void displayReceiever(void);


    private:
        MPU6050 imu;	        // inertial measurement unit 
        SFE_BMP180 pressure; 	// barametric pressure sensor
        TinyGPSPlus gps;        // possible gps library
        PPMReader reciever = PPMReader(RECIEVER_PPM_PIN, 6);    // RX in PPM mode

        Servo motor1;
        Servo motor2;
        Servo motor3;
        Servo motor4;

        struct{
            Vector3D pos;
            Vector3D vel;
            Vector3D acc;
            Quaternion orientation;
            Quaternion omega;
        }state;

        struct{
            unsigned int ch1;
            unsigned int ch2;
            unsigned int ch3;
            unsigned int ch4;
            unsigned int ch5;
            unsigned int ch6;
        }rc;
        

        void getData();
    };
}

#endif