#include "Core.h"
#include "Drone.h"
#include "Quaternion.h"
#include "Vector3D.h"

DF::Drone dragonfly;
Vector3D vect = Vector3D(1.0,1.0,1.0);
Quaternion quat = Quaternion(3.1415F, vect);

void setup() {
	Serial.begin(9600);
	//dragonfly.initialize();
	Serial.println(quat.toString());
}

void loop(){
	//////////////////////////// TODO //////////////////////////////////////
	// get raw data as quickly and often as possible					  //
	// calculate values for pos, vel, acc, orientation, and angular rate  //
	// pass values to control algorithm									  //
	// first control mode should be "stabilize" to ensure level flying	  //
	////////////////////////////////////////////////////////////////////////
	Serial.println(quat.toString());
}