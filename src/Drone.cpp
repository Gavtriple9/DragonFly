#include "Drone.h"

DF::Drone::Drone(){}

void DF::Drone::init(){

    if (!SD.begin(BUILTIN_SDCARD)) {
        Serial.println("initialization failed. No SD card found.");
    } else {
        Serial.println("SD card is present.");
    }

    Serial.println("Initializing GPS Serial");

	HWSERIAL.begin(GPSBaud);
	HWSERIAL.setRX(RXPin);
	HWSERIAL.setTX(TXPin);

    imu.setup(MPU9250_ADDRESS);
    imu.setMagneticDeclination(MAGNETIC_DECLINATION);
    imu.selectFilter(DRONE_FILTER);

    if (DEBUG_MODE) {imu.verbose(true);}
    Serial.println( imu.isConnected() ? "MPU9250 connection successful" : "MPU9250 connection failed");
    Serial.println( pressure.begin() ? "BMP180 connection successful" : "BMP180 connection failed");

    // if triggered will cause drone to shutdown all motors immediately 
    state.failSafe = false; 
    
    Serial.println( "Attaching Motors" );
    motor1.attach(MOTOR_1_PIN);
    motor2.attach(MOTOR_2_PIN);
    motor3.attach(MOTOR_3_PIN);
    motor4.attach(MOTOR_4_PIN);
    
    setAllMotors(0);
}

String DF::Drone::strStatus(){
    String rtnstr = "Dragonfly | ";
    rtnstr += "r: " + state.pos.toString(4) + " m | "; 
    rtnstr += "v: " + state.vel.toString(4) + " m/s | ";
    rtnstr += "a: " + state.acc.toString(4) + " m/s^2 | ";
    rtnstr += "q: " + state.orientation.toString(4) + " | ";
    rtnstr += "Lat: " + String(gps.location.lat(),6) + " ";
    rtnstr += "Lng: " + String(gps.location.lng(),6);
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
    } else {
        Serial.println("CRITICAL ERROR: No IMU detected. Now aborting");
        return;
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

void DF::Drone::transmitQuat(){
    Serial.println(state.orientation.toString(4));
}

void DF::Drone::update(float dt){

    // collect readings from sensors
    updateReadings();

    // update lin_acc, vel, pos, & orientation
    state.orientation = DF::Quaternion(
        imu.getQuaternionW(),
        imu.getQuaternionX(),
        imu.getQuaternionY(), 
        imu.getQuaternionZ()
    );
    if (DEBUG_MODE) {
        if ( abs(state.orientation.getX()) >= 0.35 || abs(state.orientation.getY()) >= 0.35 ) {
            setAllMotors(0);
            Serial.println("TOO FAR!");
        }
    }
    // turn orientation quaternion into rotation matrix
    state.rotMat = DF::Matrix3D(state.orientation);
    // use inverse matrix to solve for linear acc. 
    state.rotMat.inverse();
    state.acc = ((state.rotMat * DF::Vector3D(imu.getAccX(),imu.getAccY(),imu.getAccZ()))-DF::Vector3D(0,0,1))*9.81;
    
    state.vel = DF::Vector3D( 
        state.vel.getX() + state.acc.getX()*dt,
        state.vel.getY() + state.acc.getY()*dt,
        state.vel.getZ() + state.acc.getZ()*dt
    );
    state.pos = DF::Vector3D( 
        state.pos.getX() + state.vel.getX()*dt,
        state.pos.getY() + state.vel.getY()*dt,
        state.pos.getZ() + state.vel.getZ()*dt
    );
}

void DF::Drone::updateReadings(){
    if (UPDATE_RC){
        rc.ch1 = reciever.latestValidChannelValue(1, 0);
        rc.ch2 = reciever.latestValidChannelValue(2, 0);
        rc.ch3 = reciever.latestValidChannelValue(3, 0);
        rc.ch4 = reciever.latestValidChannelValue(4, 0);
        rc.ch5 = reciever.latestValidChannelValue(5, 0);
        rc.ch6 = reciever.latestValidChannelValue(6, 0);
    }
    if (UPDATE_IMU){
        imu.update();
    }
    if (UPDATE_PRESS) {
    // Update altitude 
        double temp; // perfect variable name
        double press;
        delay(pressure.startTemperature());
        pressure.getTemperature(temp);
        delay(pressure.startPressure(0));
        pressure.getPressure(press, temp);
        state.altitude = pressure.altitude(press, SEA_LEVEL_PRESSURE) - ALTITUDE;
    }
    if (UPDATE_GPS) 
    while (HWSERIAL.available()) {
		gps.encode(HWSERIAL.read());
	}
}

void DF::Drone::saveIMUData(){
    // open a new file and immediately close it:
    if (SD.exists("IMUData.txt")) {
        SD.remove("IMUData.txt");
    }
    IMUData = SD.open("IMUData.txt", FILE_WRITE);
    IMUData.println(imu.getAccBiasX());
    IMUData.println(imu.getAccBiasY());
    IMUData.println(imu.getAccBiasZ());

    IMUData.println(imu.getGyroBiasX());
    IMUData.println(imu.getGyroBiasY());
    IMUData.println(imu.getGyroBiasZ());

    IMUData.println(imu.getMagBiasX());
    IMUData.println(imu.getMagBiasY());
    IMUData.println(imu.getMagBiasZ());

    IMUData.println(imu.getMagScaleX());
    IMUData.println(imu.getMagScaleY());
    IMUData.println(imu.getMagScaleZ());
    IMUData.println("~");
    IMUData.close();
}

void DF::Drone::loadIMUData(){
    int maxCharLength = 10;

    if (SD.exists("IMUData.txt")) {

        IMUData = SD.open("IMUData.txt", FILE_READ);

        float accBiasX = (IMUData.readStringUntil('\n', maxCharLength)).toFloat();
        float accBiasY = (IMUData.readStringUntil('\n', maxCharLength)).toFloat();
        float accBiasZ = (IMUData.readStringUntil('\n', maxCharLength)).toFloat();

        float gyroBiasX = (IMUData.readStringUntil('\n', maxCharLength)).toFloat();
        float gyroBiasY = (IMUData.readStringUntil('\n', maxCharLength)).toFloat();
        float gyroBiasZ = (IMUData.readStringUntil('\n', maxCharLength)).toFloat();

        float magBiasX = (IMUData.readStringUntil('\n', maxCharLength)).toFloat();
        float magBiasY = (IMUData.readStringUntil('\n', maxCharLength)).toFloat();
        float magBiasZ = (IMUData.readStringUntil('\n', maxCharLength)).toFloat();

        float magScaleX = (IMUData.readStringUntil('\n', maxCharLength)).toFloat();
        float magScaleY = (IMUData.readStringUntil('\n', maxCharLength)).toFloat();
        float magScaleZ = (IMUData.readStringUntil('\n', maxCharLength)).toFloat();

        IMUData.close();

        imu.setAccBias(accBiasX, accBiasY, accBiasZ);
        imu.setGyroBias(gyroBiasX, gyroBiasY, gyroBiasZ);
        imu.setMagBias(magBiasX, magBiasY, magBiasZ);
        imu.setMagScale(magScaleX, magScaleY, magScaleZ);

    } else {
        Serial.println("ERROR: No calibration data found");
        Serial.println("Now running calibration");
        calibrateIMU();
    }
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