#define INTERRUPT_PIN 2
#define WAIT_TIME 100
#define PI 3.141592653589793284
#define TIME_OUT_DURATION 50

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
#include "I2Cdev.h"
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

unsigned long timeBeforeUserLoop = millis();

float yaw = 0.0f;
float pitch = 0.0f;
float roll = 0.0f;

float yawSP = 0.0f;    // degrees [-180°, 180°]
float pitchSP = 0.0f;  // degrees [-25°, 25°]
float rollSP = 0.0f;   // degrees [-25°, 25°]
float thrustSP = 0.0f; // percentage [0%, 100%]

float flightModeSP = 0.0f;
float enableSP = 0.0f;

bool isEnabled = false;

enum FlightMode
{
    stable = 0,
    acro = 1,
    freeFlight = 2
} flightMode;

String displayFlightMode = "stable";

void setup()
{
    Serial.begin(115200);
    dmpSetup();
    rcSetup();
}

void loop(){
    static uint32_t tTime[4];

    dmpLoop();

    if ((millis() - tTime[2]) >= TIME_OUT_DURATION)
    {
        tTime[2] = millis();
        Serial.println(String(tTime[2]) + "-> Yaw: " + String(yaw, 5) + "°, Pitch: " + String(pitch, 5) + "°, Roll: " + String(roll, 5) + "°");

        flightModeSP = pulseIn(CH5_PIN, HIGH);
        if (flightModeSP > 0 && flightModeSP < 1300)
        {
            flightMode = FlightMode::stable;
        }
        else if (flightModeSP > 1300 && flightModeSP < 1700)
        {
            flightMode = FlightMode::acro;
        }
        else
        {
            flightMode = FlightMode::freeFlight;
        }

        enableSP = pulseIn(CH6_PIN, HIGH);
        isEnabled = (enableSP > 1500) ? true : false;

        if (isEnabled)
        {
            yawSP = map(pulseIn(CH4_PIN, HIGH), 1020.0f, 1968.0f, -180.0f, 180.0f); // degrees
            pitchSP = map(pulseIn(CH2_PIN, HIGH), 997.0f, 1987.0f, -25.0f, 25.0f);  // degrees
            rollSP = map(pulseIn(CH1_PIN, HIGH), 997.0f, 1987.0f, -25.0f, 25.0f);   // degrees
            thrustSP = map(pulseIn(CH3_PIN, HIGH), 1000.0f, 1960.0f, 0.0f, 100.0f); // percentage
        }

        switch (flightMode)
        {
        case 0:
            displayFlightMode = "Stable";
            break;
        case 1:
            displayFlightMode = "Acro";
            break;
        case 2:
            displayFlightMode = "Free Flight";
            break;
        }

        Serial.println(String(tTime[2]) + "-> Yaw: " + String(yawSP) + ", Pitch: " + String(pitchSP) + ", Roll: " + String(rollSP) + ", Thrust: " + String(thrustSP) + ", FlightMode: " + String(displayFlightMode) + ", enable: " + String(isEnabled ? "true" : "false"));
    }
}

void dmpDataReady()
{
    mpuInterrupt = true;
}

void dmpSetup()
{
    Wire.begin();
    Wire.setClock(400000);
    TWBR = 24;

    // initialize device
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);

    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // wait for ready
    Serial.println(F("\nSend any character to begin DMP programming and demo: "));
    //  while (Serial.available() && Serial.read()); // empty buffer
    //  while (!Serial.available());                 // wait for data
    //  while (Serial.available() && Serial.read()); // empty buffer again

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(64);
    mpu.setYGyroOffset(-40);
    mpu.setZGyroOffset(36);
    //mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0)
    {
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        
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

void dmpLoop()
{
    // if programming failed, don't try to do anything
    if (!dmpReady)
        return;

    // wait for MPU interrupt or extra packet(s) available
    if (!mpuInterrupt && fifoCount < packetSize)
        return;

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024)
    {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        //  Serial.println(F("FIFO overflow!"));

        // otherwise, check for DMP data ready interrupt (this should happen frequently)
    }
    else if (mpuIntStatus & 0x02)
    {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize)
            fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);

        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

        // display Euler angles in degrees
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

        // store roll, pitch, yaw
        yaw = ypr[0] * 180 / PI;
        roll = ypr[1] * 180 / PI;
        pitch = ypr[2] * 180 / PI;
    }
}

void rcSetup() {
    // Define which pins are PWM inputs
    pinMode(CH1_PIN, INPUT);
    pinMode(CH2_PIN, INPUT);
    pinMode(CH3_PIN, INPUT);
    pinMode(CH4_PIN, INPUT);
    pinMode(CH5_PIN, INPUT);
    pinMode(CH6_PIN, INPUT);
}

