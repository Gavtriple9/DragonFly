#include "Core.h"
#include "Drone.h"

#define HWSERIAL Serial1

DF::Drone dragonfly; 

bool blinkState = false;

void setup() {
	// delay to give program time to catch up to teensy
	delay(1000);

	// Communication between 
	Serial.begin(115200);
	Serial.println("Program Start");
	Serial.println("Initializing GPS Serial");

	HWSERIAL.begin(dragonfly.GPSBaud);
	HWSERIAL.setRX(dragonfly.RXPin);
	HWSERIAL.setTX(dragonfly.TXPin);

	Serial.println("Initializing wire");
	Wire.begin();

	Serial.println("Setting wire 1");
	Wire.setSCL(SCL_PIN);
	Wire.setSDA(SDA_PIN);

	dragonfly.initialize();
	dragonfly.calibrateIMU();
}



void loop(){
	//////////////////////////// TODO //////////////////////////////////////
	// get raw data as quickly and often as possible					  //
	// calculate values for pos, vel, acc, orientation, and angular rate  //
	// pass values to control algorithm									  //
	// first control mode should be "stabilize" to ensure level flying	  //
	////////////////////////////////////////////////////////////////////////

	while (HWSERIAL.available()) {
		dragonfly.updateGPS(HWSERIAL.read());
	}

	
	dragonfly.updateReciever();
	dragonfly.displayReceiever();
  	
	dragonfly.updateReadings();
	Serial.println(dragonfly.strStatus());

	blinkState = !blinkState;	   // to signify 1 control loop cycle
	digitalWrite(LED_PIN, blinkState); // can be monitored on oscilloscope
}