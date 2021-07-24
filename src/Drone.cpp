#include "Drone.h"

DF::Drone::Drone(){

}



void DF::Drone::calibrateIMU(){
    if (imu.testConnection()) {
        Serial.println("Now calibrating gyroscope");
        imu.CalibrateGyro(CALIBRATION_LOOPS);
        Serial.println("\nOperation Complete: gyroscope is now calibrated");
        Serial.println("Now Calibrating Accelerometer");
        imu.CalibrateAccel(CALIBRATION_LOOPS);
        Serial.println("\nOperation Complete: accelerometer is now calibrated");
        imu.PrintActiveOffsets();
    }  
}

void DF::Drone::initialize(){
    imu.initialize();
    Serial.println( imu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
    Serial.println( pressure.begin() ? "BMP180 connection successful" : "BMP180 connection failed");
    filter.begin(25);
}

bool DF::Drone::testConnections(){
    return imu.testConnection();
}

void DF::Drone::getData(){
    int16_t ax, ay, az; // raw acceleration reading
    int16_t gx, gy, gz; // raw angular rate reading
    // int16_t mx, my, mz; // raw angular rate reading

    // imu.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    imu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    filter.updateIMU(
        (float) gx / GYR_SENS,
        (float) gy / GYR_SENS,
        (float) gz / GYR_SENS,
        (float) ax / ACC_SENS,
        (float) ay / ACC_SENS,
        (float) az / ACC_SENS
        // (float) mx / MAG_SENS,
        // (float) my / MAG_SENS,
        // (float) mz / MAG_SENS
    );
}

void DF::Drone::update(){
    getData();
    float u1, u2, u3, u4;
    filter.getQuaternion(&u1, &u2, &u3, &u4);
    state.orientation = Quaternion(u1, u2, u3, u4);
}

void DF::Drone::updateGPS(int ch){
    gps.encode(ch);
}

String DF::Drone::strStatus(){
    String rtnstr = "Dragonfly | r: ";
    rtnstr += state.pos.toString() + " m | v: "; 
    rtnstr += state.vel.toString() + " m/s | a: ";
    rtnstr += state.acc.toString() + " m/s^2 | q: ";
    rtnstr += state.orientation.toString(2) + " | w: ";
    rtnstr += state.omega.toString();
    rtnstr += " | Lat: " + String(gps.location.lat(),6);
    rtnstr += " | Lng: " + String(gps.location.lng(),6);
    return rtnstr;
}