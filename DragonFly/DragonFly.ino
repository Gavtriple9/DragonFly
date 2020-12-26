#define INTERRUPT_PIN 2
#define WAIT_TIME 100
#define PI 3.141592653589793284
#define TIME_OUT_DURATION 1000

#define CH1_PIN 3
#define CH2_PIN 5
#define CH3_PIN 6
#define CH4_PIN 9
#define CH5_PIN 10
#define CH6_PIN 11

//#define OUTPUT_READABLE_QUATERNION

// Standard Libraries
#include <Vector.h>
#include <Arduino.h>

// PID Library
#include <PID_v1.h>

// MPU Libraries
#include <Wire.h>
#include "MPU6050_6Axis_MotionApps20.h"
#include "MPU6050.h"

MPU6050 mpu = MPU6050(0x68);

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q = Quaternion(1, 0, 0, 0); // [w, x, y, z]         quaternion container
VectorInt16 aa;                        // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;                    // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;                   // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;                   // [x, y, z]            gravity vector
float euler[3];                        // [psi, theta, phi]    Euler angle container
float ypr[3];                          // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

volatile bool mpuInterrupt = false; // indicates whether MPU interrupt pin has gone high

unsigned long timeBeforeLoop;

float yaw = 0.0f;
float pitch = 0.0f;
float roll = 0.0f;

void setup()
{
    Serial.begin(115200);
    mpuSetup();
    rcSetup();
}

void loop()
{
    // if programming failed, don't try to do anything
    if (!dmpReady)
        return;
    // wait for MPU interrupt or extra packet(s) available
    if ( millis() - timeBeforeLoop > TIME_OUT_DURATION){
        mpuInterrupt = false;
        mpu.resetFIFO();
        fifoCount = mpu.getFIFOCount();
    }   
    while (!mpuInterrupt && fifoCount < packetSize)
    {
        timeBeforeLoop = millis();
        if (mpuInterrupt && fifoCount < packetSize)
        {
            // try to get out of the infinite loop
            mpu.resetFIFO();
        }
        // Now have access to yaw, pitch, and roll values
        Serial.println(String(millis()) + "-> Yaw: " + String(yaw, 5) + "°, Pitch: " + String(pitch, 5) + "°, Roll: " + String(roll, 5) + "°");
        
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & _BV(MPU6050_INTERRUPT_FIFO_OFLOW_BIT)) || fifoCount >= 1024)
    {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        fifoCount = mpu.getFIFOCount();
        Serial.println(F("FIFO overflow!"));

        // otherwise, check for DMP data ready interrupt (this should happen frequently)
    }
    else if (mpuIntStatus & _BV(MPU6050_INTERRUPT_DMP_INT_BIT))
    {
        // wait for correct available data length, should be a VERY short wait

        // TODO: Create a max time to wait so infinte loops don't occur.
        
        while (fifoCount < packetSize){
            fifoCount = mpu.getFIFOCount();
        }

            // read a packet from FIFO
            mpu.getFIFOBytes(fifoBuffer, packetSize);
            mpu.resetFIFO();


        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        yaw = ypr[0] * 180 / M_PI;
        pitch = ypr[1] * 180 / M_PI;
        roll = ypr[2] * 180 / M_PI;
    }
}

void dmpDataReady()
{
    mpuInterrupt = !mpuInterrupt;
}

void printQuat(Quaternion q)
{
    Serial.print("quat\t");
    Serial.print(q.w);
    Serial.print("\t");
    Serial.print(q.x);
    Serial.print("\t");
    Serial.print(q.y);
    Serial.print("\t");
    Serial.println(q.z);
}

void mpuSetup()
{

    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);

    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(64);
    mpu.setYGyroOffset(-53);
    mpu.setZGyroOffset(36);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0)
    {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    }
    else
    {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }
}

void rcSetup(){
    pinMode(CH1_PIN, INPUT);
    pinMode(CH2_PIN, INPUT);
    pinMode(CH3_PIN, INPUT);
    pinMode(CH4_PIN, INPUT);
    pinMode(CH5_PIN, INPUT);
    pinMode(CH6_PIN, INPUT);

}