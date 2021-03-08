#include "Core.h"
#include <string.h>
#define LED_PIN 13

MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;

String buffer;

bool blinkState = false;

void setup(){
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
	  
	Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loop()
{

	mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	blinkState = !blinkState;
	digitalWrite(LED_PIN, blinkState);

	Serial.print("a/g:\t");
    Serial.print(ax); Serial.print("\t");
    Serial.print(ay); Serial.print("\t");
    Serial.print(az); Serial.print("\t");
    Serial.print(gx); Serial.print("\t");
    Serial.print(gy); Serial.print("\t");
    Serial.println(gz);
	
	// Serial.println(buffer);
	// Collect data from sensors
	// Process data
  	// Output data
}