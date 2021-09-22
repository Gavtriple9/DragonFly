#pragma once
#ifndef DRONE_H
#define DRONE_H

#include "Core.h"

#include <Servo.h>
#include <PPMReader.h>
#include <SFE_BMP180.h>
#include <TinyGPS++.h>
#include <MPU9250.h>
#include <SD.h>
#include <SPI.h>


#include "Quaternion.h"
#include "Matrix3D.h"

namespace DF {
    class Drone {
    public:
        static const int RXPin = 0, TXPin = 1;
        static const uint32_t GPSBaud = 9600;

        Drone();
        // Drone functions
        void init(void);
        String strStatus();
        void calibrateIMU(void);
        void update(float dt);
        void saveIMUData();
        void loadIMUData();
    
        void getUserCommand(void); // from keyboard (temp function)
        
        // Motor control functions
        void setMotor1Speed(float);
        void setMotor2Speed(float);
        void setMotor3Speed(float);
        void setMotor4Speed(float);
        void setAllMotors(float);

        void calibrateMotors(void);
        
        // Controller collected data
        void displayReceiever(void);

        String transmitQuat(void);


    private:
        // Sensor objects  
        MPU9250 imu;	        // inertial measurement unit 
        SFE_BMP180 pressure; 	// barametric pressure sensor
        TinyGPSPlus gps;        // possible gps library
        PPMReader reciever = PPMReader(RECIEVER_PPM_PIN, 6);    // RX in PPM mode

        // Motor objects
        Servo motor1;
        Servo motor2;
        Servo motor3;
        Servo motor4;

        File IMUData;

        struct{
            float altitude;
            Vector3D pos;
            Vector3D vel;
            Vector3D acc;
            Quaternion orientation;
            Matrix3D rotMat;
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

        void updateReadings();

    };
}

#endif