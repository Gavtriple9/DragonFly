#include "Drone.h"
#include "MPU6050.h"
#include <Wire.h>

Drone dragonFly;
MPU6050 mpu = MPU6050(0x68);

void setup() {
    // put your setup code here, to run once:
    
    Serial.begin(9600); 
    dragonFly.setMotor1(4);
    //mpu.initialize();
    dragonFly.calibrateMotors();
}

void loop() {
    dragonFly.controlManually();
//    Serial.println(mpu.testConnection());
//    if (mpu.testConnection()){
//        Serial.println(mpu.getAccelerationX());
//    }
}
