#include "Drone.h"

DF::Drone::Drone(){
    
}

void DF::Drone::initialize(){

    Serial.println("Initializing GPS Serial");

	HWSERIAL.begin(GPSBaud);
	HWSERIAL.setRX(RXPin);
	HWSERIAL.setTX(TXPin);

    imu.setup(MPU9250_ADDRESS);
    imu.setMagneticDeclination(MAGNETIC_DECLINATION);
    imu.selectFilter(QuatFilterSel::MAHONY);

    if (DEBUG_MODE) {imu.verbose(true);}
    Serial.println( imu.isConnected() ? "MPU9250 connection successful" : "MPU9250 connection failed");
    Serial.println( pressure.begin() ? "BMP180 connection successful" : "BMP180 connection failed");

    Serial.println( "Attaching Motors" );
    motor1.attach(MOTOR_1_PIN);
    motor2.attach(MOTOR_2_PIN);
    motor3.attach(MOTOR_3_PIN);
    motor4.attach(MOTOR_4_PIN);
    setAllMotors(0);

}

String DF::Drone::strStatus(){
    String rtnstr = "Dragonfly | r: ";
    rtnstr += String(state.altitude) + " m | v: "; 
    rtnstr += state.vel.toString() + " m/s | a: ";
    rtnstr += state.acc.toString() + " m/s^2 | q: ";
    rtnstr += state.orientation.toString(2) + " | w: ";
    rtnstr += state.omega.toString();
    rtnstr += " | Lat: " + String(gps.location.lat(),6);
    rtnstr += " | Lng: " + String(gps.location.lng(),6);
    return rtnstr;
}

void DF::Drone::calibrateIMU(){
    if (imu.isConnected()) {
        Serial.println("Now calibrating gyroscope and accelerometer");
        imu.calibrateAccelGyro();
        Serial.println("\nOperation Complete");
        Serial.println("Now calibrating magnetometer");
        imu.calibrateMag();
        Serial.println("\nOperation Complete");
    }  
}

void DF::Drone::getUserCommand(){
    String speedString = "";
    while(Serial.available()){
		int currRead = Serial.read();
        // 10 is new line '/n' and interpreted as a finished command
		if( currRead == 10 ){
            if ( speedString == "0" ) {
				setAllMotors(0);
			}
			else if ( speedString == "test" ){
				setAllMotors(20); // 20% Thrust test
			} 
			else if ( speedString == "1" ) {
				setMotor1Speed(20);
			} 
			else if ( speedString == "2" ) {
				setMotor2Speed(20);
			} 
			else if ( speedString == "3" ) {
				setMotor3Speed(20);
			} 
			else if ( speedString == "4" ) {
				setMotor4Speed(20);
			} 
			else if ( speedString == "max" ) {
				setAllMotors(100);
			} 
			else if ( speedString == "cal" ) {
				calibrateMotors();
			} 
			speedString = "";
		}
		else {
            // 10 is new line <nl> and 13 is carriage return <cr>
			if (currRead != 10 && currRead != 13){ 
				speedString += char(currRead);
			}
		}
	}
};

String DF::Drone::transmitQuat(){
    return state.orientation.toString(4);
}

void DF::Drone::update(){
    updateReadings();
    //updateReciever();
    state.orientation = DF::Quaternion(
        imu.getQuaternionW(),
        imu.getQuaternionX(),
        imu.getQuaternionY(), 
        imu.getQuaternionZ()
    );
}

void DF::Drone::updateReadings(){
    // update lin_acc, vel, pos, & orientation
    imu.update();
    
    // Update altitude 
    double temp; // perfect variable name
    double press;
    delay(pressure.startTemperature());
    pressure.getTemperature(temp);
    delay(pressure.startPressure(0));
    pressure.getPressure(press, temp);
    state.altitude = pressure.altitude(press, SEA_LEVEL_PRESSURE) - ALTITUDE;

    while (HWSERIAL.available()) {
		gps.encode(HWSERIAL.read());
	}
}

void DF::Drone::updateReciever(void){
    rc.ch1 = reciever.latestValidChannelValue(1, 0);
    rc.ch2 = reciever.latestValidChannelValue(2, 0);
    rc.ch3 = reciever.latestValidChannelValue(3, 0);
    rc.ch4 = reciever.latestValidChannelValue(4, 0);
    rc.ch5 = reciever.latestValidChannelValue(5, 0);
    rc.ch6 = reciever.latestValidChannelValue(6, 0);
}

void DF::Drone::displayReceiever(){
    Serial.println(
        "Ch1: " + String(rc.ch1) 
        + " Ch2: " + String(rc.ch2) 
        + " Ch3: " + String(rc.ch3) 
        + " Ch4: " + String(rc.ch4)
        + " Ch5: " + String(rc.ch5)
        + " Ch6: " + String(rc.ch6) + "\n"
    );
}

void DF::Drone::setMotor1Speed(float speed){
    float temp = map(speed, 0, 100, MIN_MOTOR_SPEED, MAX_MOTOR_SPEED);
    motor1.writeMicroseconds(temp);
}
void DF::Drone::setMotor2Speed(float speed){
    float temp = map(speed, 0, 100, MIN_MOTOR_SPEED, MAX_MOTOR_SPEED);
    motor2.writeMicroseconds(temp);
}
void DF::Drone::setMotor3Speed(float speed){
    float temp = map(speed, 0, 100, MIN_MOTOR_SPEED, MAX_MOTOR_SPEED);
    motor3.writeMicroseconds(temp);
}
void DF::Drone::setMotor4Speed(float speed){
    float temp = map(speed, 0, 100, MIN_MOTOR_SPEED, MAX_MOTOR_SPEED);
    motor4.writeMicroseconds(temp);
}

void DF::Drone::setAllMotors(float speed){ 
    float temp = map(speed, 0, 100, MIN_MOTOR_SPEED, MAX_MOTOR_SPEED);
    motor1.writeMicroseconds(temp);
    motor2.writeMicroseconds(temp);
    motor3.writeMicroseconds(temp);
    motor4.writeMicroseconds(temp);
}

void DF::Drone::calibrateMotors(void){
    setAllMotors(100);
    Serial.println("Motors at 100%");
    delay(3000);
    setAllMotors(0);
    Serial.println("Motors at 0%");
    delay(3000);
    setAllMotors(100);
    Serial.println("Motors at 10%");
    delay(3000);
    setAllMotors(0);
    Serial.println("Motors at 0%");
    Serial.println("Motors have been successfully calibrated!");
}