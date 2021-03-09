#include "Core.h"
#include <string.h>
#define LED_PIN 13
#define BMP085_ADDRESS 0x77

MPU6050 mpu;	// inertial measurement unit 
BMP180 bmp(2); 	// barametric pressure sensor

int16_t ax, ay, az; // raw acceleration reading
int16_t gx, gy, gz; // raw angular rate reading

float temp; 	// temperature ºC (Celcius)
float press;	// pressure Pa (pascals)
float alti;		// altitude m (meters)

float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ; // acceleration m/s^2
float roll, pitch, yaw; // degrees

bool blinkState = false;

void printData(void);

void setup() {
	Serial.begin(115200);
	Serial.println("Initializing wire");
	Wire.begin();
	Wire1.begin();
	Serial.println("Setting wire 1");
	Wire.setSCL(19);
	Wire.setSDA(18);
	Serial.println("Setting wire 2");
	Wire1.setSCL(16);
	Wire1.setSDA(17);
	mpu.initialize();
	bmp.initialize();

	Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loop()
{

	// Collect data from sensors
	mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	bmp.getValues(&temp, &press, &alti);

	// Process data
	// kalman filter for Gyro & Accel
	// Output data

	blinkState = !blinkState; // to signify 1 control loop cycle
	digitalWrite(LED_PIN, blinkState); // can be monitored on oscilloscope
}

void printData(void){
	Serial.print("Temperature: ");
	Serial.print(temp, 2); //display 2 decimal places
	Serial.println("deg C");

	Serial.print("Pressure: ");
	Serial.print(press, 0); //whole number only.
	Serial.println(" Pa");

	Serial.print("Altitude: ");
	Serial.print(alti, 2); //display 2 decimal places
	Serial.println(" M");

	Serial.print("a/g:\t");
	Serial.print(ax);
	Serial.print("\t");
	Serial.print(ay);
	Serial.print("\t");
	Serial.print(az);
	Serial.print("\t");
	Serial.print(gx);
	Serial.print("\t");
	Serial.print(gy);
	Serial.print("\t");
	Serial.println(gz);
}