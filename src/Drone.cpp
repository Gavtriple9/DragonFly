#include "Drone.h"

DF::Drone::Drone(){
    
}

void DF::Drone::calibrateIMU(){
    if (imu.testConnection()) {
        Serial.println("Now calibrating gyroscope");
        imu.CalibrateGyro(CALIBRATION_LOOPS);
        Serial.println("\nOperation Complete: gyroscope is now calibrated");
        Serial.println("Now Calibrating Accelerometer");
        imu.CalibrateAccel(CALIBRATION_LOOPS);
        Serial.println("\nOperation Complete: accelerometer is now calibrated");
        imu.PrintActiveOffsets();
    }  
}

void DF::Drone::getUserCommand(){
    String speedString = "";
    while(Serial.available()){
		int currRead = Serial.read();
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

void DF::Drone::initialize(){

    imu.initialize();
    Serial.println( imu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
    Serial.println( pressure.begin() ? "BMP180 connection successful" : "BMP180 connection failed");

    Serial.println( "Attaching Motors" );
    motor1.attach(MOTOR_1_PIN);
    motor2.attach(MOTOR_2_PIN);
    motor3.attach(MOTOR_3_PIN);
    motor4.attach(MOTOR_4_PIN);
    setAllMotors(0);
}

bool DF::Drone::testConnections(){
    return imu.testConnection();
}

void DF::Drone::getData(){
    int16_t ax, ay, az; // raw acceleration reading
    int16_t gx, gy, gz; // raw angular rate reading
    int16_t mx, my, mz; // raw B field direction reading

    imu.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    Serial.println(
        "Ax: " + String(ax) 
        + " Ay: " + String(ay) 
        + " Az: " + String(az) 
        + " Gx: " + String(gx)
        + " Gy: " + String(gy)
        + " Gz: " + String(gz)
        + " Mx: " + String(mx)
        + " My: " + String(my)
        + " Mz: " + String(mz) + "\n"
    );
}

void DF::Drone::updateReadings(){
    getData();
    state.orientation = Quaternion(0, 0, 0, 0);
}

void DF::Drone::updateGPS(int ch){
    gps.encode(ch);
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

String DF::Drone::strStatus(){
    String rtnstr = "Dragonfly | r: ";
    rtnstr += state.pos.toString() + " m | v: "; 
    rtnstr += state.vel.toString() + " m/s | a: ";
    rtnstr += state.acc.toString() + " m/s^2 | q: ";
    rtnstr += state.orientation.toString(2) + " | w: ";
    rtnstr += state.omega.toString();
    rtnstr += " | Lat: " + String(gps.location.lat(),6);
    rtnstr += " | Lng: " + String(gps.location.lng(),6);
    return rtnstr;
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