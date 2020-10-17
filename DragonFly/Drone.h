#include <Servo.h>
#include <Arduino.h>

#include "Quaternion.h"
#include "MPU6050.h"

class Drone{
private:
    Servo motor1;
    Servo motor2;
    Servo motor3;
    Servo motor4;

    Quaternion angle;

    int minSPM1 = 1000;
    int minSPM2 = 1000;
    int minSPM3 = 1000;
    int minSPM4 = 1000;

    int maxSPM1 = 2000;
    int maxSPM2 = 2000;
    int maxSPM3 = 2000;
    int maxSPM4 = 2000;
    
public:
    Drone();

    Quaternion getAngle(void);

    void setMinSPM1(int arg1){ minSPM1 = arg1; }
    void setMinSPM2(int arg1){ minSPM2 = arg1; }
    void setMinSPM3(int arg1){ minSPM3 = arg1; }
    void setMinSPM4(int arg1){ minSPM4 = arg1; }
    
    void setMaxSPM1(int arg1){ maxSPM1 = arg1; }
    void setMaxSPM2(int arg1){ maxSPM2 = arg1; }
    void setMaxSPM3(int arg1){ maxSPM3 = arg1; }
    void setMaxSPM4(int arg1){ maxSPM4 = arg1; }

    int getMinSPM1(void){ return minSPM1; }
    int getMinSPM2(void){ return minSPM2; }
    int getMinSPM3(void){ return minSPM3; }
    int getMinSPM4(void){ return minSPM4; }
    
    int getMaxSPM1(void){ return maxSPM1; }
    int getMaxSPM2(void){ return maxSPM2; }
    int getMaxSPM3(void){ return maxSPM3; }
    int getMaxSPM4(void){ return maxSPM4; }

    void setMotor1(int);
    void setMotor2(int);
    void setMotor3(int);
    void setMotor4(int);
    void setMotors(int,int,int,int);

    void setMotor1Speed(float);
    void setMotor2Speed(float);
    void setMotor3Speed(float);
    void setMotor4Speed(float);
    void setMotorSpeeds(float,float,float,float);
    
    void calibrateMotors(void);
    void controlManually(void);
};
