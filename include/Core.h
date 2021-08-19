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

// I2C pins
#define SDA_PIN 18
#define SCL_PIN 19

// Motor pins
#define MOTOR_1_PIN 2
#define MOTOR_2_PIN 3
#define MOTOR_3_PIN 4
#define MOTOR_4_PIN 6

// Reciever pin
#define RECIEVER_PPM_PIN 7

#define MAX_MOTOR_SPEED 2000
#define MIN_MOTOR_SPEED 1000

#define BMP180_ADDRESS 0x77
#define MPU9250_ADDRESS 0x68

#define ACC_SENS 16384.0
#define GYR_SENS 131.0
#define MAG_SENS 0.6

#define RADTODEG(n) n*57.2957795131
#define DEGTORAD(n) n*0.01745329251

#endif