#pragma once
#ifndef CORE_H
#define CORE_H

#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include <string.h>
#include <map>
#include <SoftwareSerial.h>

#define DEBUG_MODE true
#define CALIBRATE_DRONE false

// #define DRONE_FILTER QuatFilterSel::MADGWICK 
#define DRONE_FILTER QuatFilterSel::MAHONY

// update specific sensors
#define UPDATE_RC false
#define UPDATE_IMU true
#define UPDATE_PRESS false
#define UPDATE_GPS true

#define HWSERIAL Serial1

// Constants
#define ALTITUDE 68 // m
#define SEA_LEVEL_PRESSURE 1010.845f // mBar
#define MAGNETIC_DECLINATION 11.00611f // degrees
#define EARTH_CENTER_TO_SEALEVEL 6371146 // m

#define MAX_MOTOR_SPEED 2000
#define MIN_MOTOR_SPEED 1000

#define BMP180_ADDRESS 0x77
#define MPU9250_ADDRESS 0x68

#define ACC_SENS 16384.0
#define GYR_SENS 131.0
#define MAG_SENS 0.6

#define RADTODEG(n) n*57.2957795131
#define DEGTORAD(n) n*0.01745329251

// Motor pins
#define MOTOR_1_PIN 2
#define MOTOR_2_PIN 3
#define MOTOR_3_PIN 4
#define MOTOR_4_PIN 6

// Reciever pin
#define RECIEVER_PPM_PIN 7

// Ultrasonic sensor
#define TRIG_PIN 8
#define ECHO_PIN 9

// Board LED and control loop frequency (CLF)
#define LED_PIN 13

// I2C pins
#define SDA_PIN 18
#define SCL_PIN 19


#endif