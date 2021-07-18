#include "Drone.h"

DF::Drone::Drone(){
    // bmp = BMP180(2);
}

void DF::Drone::calibrateIMU(){
    bool connected = imu.testConnection();
    Serial.println( connected ? "MPU6050 connection successful" : "MPU6050 connection failed");
    if (connected) {
        Serial.println("Now calibrating gyroscope");
        imu.CalibrateGyro();
        Serial.println("\nOperation Complete: gyroscope is now calibrated");
        Serial.println("Now Calibrating Accelerometer");
        imu.CalibrateAccel();
        Serial.println("\nOperation Complete: accelerometer is now calibrated");
        imu.PrintActiveOffsets();
    }  
}

void DF::Drone::initialize(){
    imu.initialize();
    // bmp.initialize();
}
