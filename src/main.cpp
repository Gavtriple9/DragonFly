#include "Core.h"

#define LED_PIN 13
#define BMP085_ADDRESS 0x77
#define ACC_SENS 16384.0
#define GYR_SENS 131.0
#define RADTODEG 57.2957795131
#define DEGTORAD 0.01745329251

MPU6050 mpu;	// inertial measurement unit 
BMP180 bmp(2); 	// barametric pressure sensor
TinyGPSPlus gps; // possible gps library

PID yawPid(1, 1, 1); // kP = 1, kI = 1, kD = 1

struct {
	float rollCommand = 0.0f;
	float pitchCommand = 0.0f;
	float yawCommand = 0.0f;

} pidCommands;

int16_t ax, ay, az; // raw acceleration reading
int16_t gx, gy, gz; // raw angular rate reading

float accX, accY, accZ; // float converison
float gyroX, gyroY, gyroZ; // float converison

float temp; 	// temperature ºC (Celcius)
float press;	// pressure Pa (pascals)
float alti;		// altitude m (meters)

float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ; // acceleration m/s^2
float roll, pitch, yaw; // degrees 

float now, prevTime, dt; // milliseconds ms

bool blinkState = false;

void printData(void);
void displayInfo();

void setup() {
	now = 0.0f; // initialize drone internal clock to 0
	Serial.begin(115200);

	Serial.println("Initializing wire");
	Wire.begin();

	Serial.println("Setting wire 1");
	Wire.setSCL(19);
	Wire.setSDA(18);

	Serial.println("Setting wire 2");

	mpu.initialize();
	bmp.initialize();

	delay(2000); // give time for drone to settle
	Serial.println("Now calibrating gyroscope");
	mpu.CalibrateGyro();
	Serial.println("\nOperation Complete: gyroscope is now calibrated");
	Serial.println("Now Calibrating Accelerometer");
	mpu.CalibrateAccel();
	Serial.println("\nOperation Complete: accelerometer is now calibrated");
	mpu.PrintActiveOffsets();

	Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loop()
{
	prevTime = now;
	now = millis(); // the time at the start of the next loop
	dt = (now - prevTime) / 1000; // time step in seconds

	// Collect data from sensors
	mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	bmp.getValues(&temp, &press, &alti);

	// Process data
	gyroX = (float) gx / GYR_SENS;
	gyroY = (float) gy / GYR_SENS;
	gyroZ = (float) gz / GYR_SENS;

	accX = (float) ax / ACC_SENS;
	accY = (float) ay / ACC_SENS;
	accZ = (float) az / ACC_SENS;

	gyroAngleX = gyroAngleX + gyroX * dt;
	gyroAngleY = gyroAngleY + gyroY * dt;
	yaw = yaw + gyroZ * dt;

	accAngleX = (atan(accY / sqrt(accX * accX + accZ * accZ)) * RADTODEG);
	accAngleY = (atan(-1 * accX / sqrt(accY * accY + accZ * accZ)) * RADTODEG);

	// kalman filter for Gyro & Accel
	roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
	pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;

	// TODO

	// PID loops

	// translate data into torques and forces

	// Output data to motors
	printData();


	blinkState = !blinkState;	   // to signify 1 control loop cycle
	digitalWrite(LED_PIN, blinkState); // can be monitored on oscilloscope
}


void printData(void)
{

	Serial.print(roll);
	Serial.print("/");
	Serial.print(pitch);
	Serial.print("/");
	Serial.println(yaw);

	// Print barameter
	Serial.print("Temperature: ");
	Serial.print(temp, 2);
	Serial.println("deg C");

	Serial.print("Pressure: ");
	Serial.print(press, 0);
	Serial.println(" Pa");

	Serial.print("Altitude: ");
	Serial.print(alti, 2);
	Serial.println(" M");

	Serial.println();
}