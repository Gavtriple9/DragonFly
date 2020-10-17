#include "Drone.h"

Drone::Drone(){}

void Drone::setMotor1(int port){
    motor1.attach(port, getMinSPM1(), getMaxSPM1());
}
void Drone::setMotor2(int port){
    motor2.attach(port, getMinSPM2(), getMaxSPM2());
}
void Drone::setMotor3(int port){
    motor3.attach(port, getMinSPM3(), getMaxSPM3());
}
void Drone::setMotor4(int port){
    motor4.attach(port, getMinSPM4(), getMaxSPM4());
}

void Drone::setMotors(int port1, int port2, int port3, int port4){
    motor1.attach(port1);
    motor2.attach(port2);
    motor3.attach(port3);
    motor4.attach(port4);
}


void Drone::setMotor1Speed(float arg1){
    float temp = map(arg1, 0, 100, getMinSPM1(), getMaxSPM1());
    motor1.writeMicroseconds(temp);
}
void Drone::setMotor2Speed(float arg1){
    float temp = map(arg1, 0, 100, getMinSPM2(), getMaxSPM2());
    motor2.writeMicroseconds(temp);
}
void Drone::setMotor3Speed(float arg1){
    float temp = map(arg1, 0, 100, getMinSPM3(), getMaxSPM3());
    motor3.writeMicroseconds(temp);
}
void Drone::setMotor4Speed(float arg1){
    float temp = map(arg1, 0, 100, getMinSPM4(), getMaxSPM4());
    motor4.writeMicroseconds(temp);
}

void Drone::setMotorSpeeds(float arg1,float arg2, float arg3, float arg4){
    float temp1 = map(arg1, 0, 100, getMinSPM1(), getMaxSPM1());
    float temp2 = map(arg2, 0, 100, getMinSPM2(), getMaxSPM2());
    float temp3 = map(arg3, 0, 100, getMinSPM3(), getMaxSPM3());
    float temp4 = map(arg4, 0, 100, getMinSPM4(), getMaxSPM4());
    
    motor1.writeMicroseconds(temp1);
    motor2.writeMicroseconds(temp2);
    motor3.writeMicroseconds(temp3);
    motor4.writeMicroseconds(temp4);
}

Quaternion Drone::getAngle(void){
    
    
}

void Drone::controlManually(void){
    if (Serial.available() > 0) {
        int value = Serial.read();
        switch( value ){
            case '0':
                setMotor1Speed(0);
                Serial.println("Motors now at 0%");
                break;
            case '1':
                setMotor1Speed(5);
                Serial.println("Motors now at 5%");
                break;
            case '2':
                setMotor1Speed(10);
                Serial.println("Motors now at 10%");
                break;
            case '3':
                setMotor1Speed(15);
                Serial.println("Motors now at 15%");
                break;
            case '4':
                setMotor1Speed(20);
                Serial.println("Motors now at 20%");
                break;
            case '5':
                setMotor1Speed(25);
                Serial.println("Motors now at 25%");
                break;
            case '6':
                setMotor1Speed(30);
                Serial.println("Motors now at 30%");
                break;
            case '7':
                setMotor1Speed(35);
                Serial.println("Motors now at 35%");
                break;
            case '8':
                setMotor1Speed(40);
                Serial.println("Motors now at 40%");
                break;
            case '9':
                setMotor1Speed(45);
                Serial.println("Motors now at 45%");
                break;
            case 'a':
                setMotor1Speed(50);
                Serial.println("Motors now at 50%");
                break;
            case 'z':
                setMotor1Speed(100);
                Serial.println("Motors now at 100%");
                break;
            case 'l':
                setMotor1Speed(2);
                Serial.println("Motors now at 1%");
                break;
        }
    } 
}

void Drone::calibrateMotors(void){
    setMotor1Speed(100);
    Serial.println("Motors at 100%");
    Serial.println("press enter to continue");
    while(!Serial.available()){}
    setMotor1Speed(0);
    Serial.println("Motors at 0%");
    Serial.println("press enter to continue");
    Serial.read();
    while(!Serial.available()){}
    setMotor1Speed(100);
    Serial.println("Motors at 100%");
    Serial.println("press enter to continue");
    Serial.read();
    while(!Serial.available()){}
    setMotor1Speed(0);
    Serial.println("Motors at 0%");
    Serial.println("press enter to continue");
    Serial.read();
    while(!Serial.available()){}
    Serial.println("Motors have been successfully calibrated!");
}
