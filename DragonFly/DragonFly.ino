#include "Drone.h"
#include "MPU6050.h"
#include <Wire.h>

Drone dragonFly;
MPU6050 mpu = MPU6050(0x68);

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600); 

}

void loop() {
    Serial.println("Hello");
    delay(1000);
}
