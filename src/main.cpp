#include "Core.h"
#include "Drone.h"

DF::Drone dragonfly; 

bool blinkState = false;

// global drone timing variables
float currentTime = 0;
float prevTime = 0;
float dt = 0;



void setup() {
	// delay to give program time to catch up to teensy
	delay(1000);

	// Communication between 
	Serial.begin(115200);
	Serial.println("Program Start");

	Serial.println("Initializing wire");
	Wire.begin();

	Serial.println("Setting wire 1");
	Wire.setSCL(SCL_PIN);
	Wire.setSDA(SDA_PIN);

	dragonfly.init();
	
	if ( CALIBRATE_DRONE ){
		dragonfly.calibrateIMU();
    	dragonfly.saveIMUData();
	} else { dragonfly.loadIMUData(); }
  
}

void loop(){
	currentTime = micros();
	if ( prevTime != 0 ){
		dt = currentTime - prevTime;
		dt /= 1000000; // convert to seconds
		//Serial.println(dt,6);
	}
	//////////////////////////// TODO //////////////////////////////////////
	// get raw data as quickly and often as possible					  //
	// calculate values for pos, vel, acc, orientation, and angular rate  //
	// pass values to control algorithm									  //
	// first control mode should be "stabilize" to ensure level flying	  //
	////////////////////////////////////////////////////////////////////////

	dragonfly.update(dt);
	//dragonfly.displayReceiever();
  	
	// Serial.println(dragonfly.strStatus());
	dragonfly.transmitQuat();



	blinkState = !blinkState;	   // to signify 1 control loop cycle
	digitalWrite(LED_PIN, blinkState); // can be monitored on oscilloscope
	prevTime = currentTime;
} 