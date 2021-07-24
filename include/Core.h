#pragma once
#ifndef CORE_H
#define CORE_H

#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include <string.h>
#include <map>
#include <SoftwareSerial.h>

#define LED_PIN 13

#define SDA_PIN 18
#define SCL_PIN 19

#define BMP180_ADDRESS 0x77
#define MPU6050_ADDRESS 0x68
#define ACC_SENS 16384.0
#define GYR_SENS 131.0
// #define MAG_SENS 
#define RADTODEG 57.2957795131
#define DEGTORAD 0.01745329251

#endif