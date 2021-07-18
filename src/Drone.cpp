#include "Drone.h"

DF::Drone::Drone(){

}

void DF::Drone::calibrateIMU(){
    if (imu.testConnection()) {
        Serial.println("Now calibrating gyroscope");
        imu.CalibrateGyro(CALIBRATION_PASSES);
        Serial.println("\nOperation Complete: gyroscope is now calibrated");
        Serial.println("Now Calibrating Accelerometer");
        imu.CalibrateAccel(CALIBRATION_PASSES);
        Serial.println("\nOperation Complete: accelerometer is now calibrated");
        imu.PrintActiveOffsets();
    }  
}

void DF::Drone::initialize(){
    imu.initialize();
    Serial.println( imu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
    Serial.println( pressure.begin() ? "BMP180 connection successful" : "BMP180 connection failed");
}

bool DF::Drone::testConnections(){
    return imu.testConnection();
}