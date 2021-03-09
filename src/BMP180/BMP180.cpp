#include "BMP180.h"

BMP180::BMP180(unsigned int i)
{
    if (i <= 3)
    {
        OSS = i;
    }
    else
    {
        OSS = 0;
    }
}

void BMP180::getValues(float* T, float* P, float* A){
    *T = getTemperature(readUT());
    *P = getPressure(readUP());
    *A = calcAltitude(*P);
}

// Stores all of the bmp085's calibration values into global variables
// Calibration values are required to calculate temp and pressure
// This function should be called at the beginning of the program
void BMP180::initialize()
{
  ac1_m = readInt(0xAA);
  ac2_m = readInt(0xAC);
  ac3_m = readInt(0xAE);
  ac4_m = readInt(0xB0);
  ac5_m = readInt(0xB2);
  ac6_m = readInt(0xB4);
  b1_m = readInt(0xB6);
  b2_m = readInt(0xB8);
  mb_m = readInt(0xBA);
  mc_m = readInt(0xBC);
  md_m = readInt(0xBE);
}

// Calculate temperature in deg C
float BMP180::getTemperature(unsigned int ut){
    long x1, x2;

    x1 = (((long)ut - (long)ac6_m)*(long)ac5_m) >> 15;
    x2 = ((long)mc_m << 11)/(x1 + md_m);
    b5_m = x1 + x2;

    float temp = ((b5_m + 8)>>4);
    temp = temp /10;

    return temp;
}

// Calculate pressure given up
// calibration values must be known
// b5 is also required so bmp085GetTemperature(...) must be called first.
// Value returned will be pressure in units of Pa.
long BMP180::getPressure(unsigned long up){
    long x1, x2, x3, b3, b6, p;
    unsigned long b4, b7;

    b6 = b5_m - 4000;
    // Calculate B3
    x1 = (b2_m * (b6 * b6)>>12)>>11;
    x2 = (ac2_m * b6)>>11;
    x3 = x1 + x2;
    b3 = (((((long)ac1_m)*4 + x3)<<OSS) + 2)>>2;

    // Calculate B4
    x1 = (ac3_m * b6)>>13;
    x2 = (b1_m * ((b6 * b6)>>12))>>16;
    x3 = ((x1 + x2) + 2)>>2;
    b4 = (ac4_m * (unsigned long)(x3 + 32768))>>15;

    b7 = ((unsigned long)(up - b3) * (50000>>OSS));
    if (b7 < 0x80000000)
        p = (b7<<1)/b4;
    else
        p = (b7/b4)<<1;

    x1 = (p>>8) * (p>>8);
    x1 = (x1 * 3038)>>16;
    x2 = (-7357 * p)>>16;
    p += (x1 + x2 + 3791)>>4;

    long temp = p;
    return temp;
}

// Read 1 byte from the BMP085 at 'address'
char BMP180::read(unsigned char address)
{
    Wire1.beginTransmission(BMP180_ADDRESS);
    Wire1.write(address);
    Wire1.endTransmission();

    Wire1.requestFrom(BMP180_ADDRESS, 1);
    while(!Wire1.available())
        ;

    return Wire1.read();
}

// Read 2 bytes from the BMP085
// First byte will be from 'address'
// Second byte will be from 'address'+1
int BMP180::readInt(unsigned char address)
{
    unsigned char msb, lsb;

    Wire1.beginTransmission(BMP180_ADDRESS);
    Wire1.write(address);
    Wire1.endTransmission();

    Wire1.requestFrom(BMP180_ADDRESS, 2);
    while(Wire1.available()<2)
        ;
    msb = Wire1.read();
    lsb = Wire1.read();

    return (int) msb<<8 | lsb;
}

// Read the uncompensated temperature value
unsigned int BMP180::readUT(){
    unsigned int ut;

    // Write 0x2E into Register 0xF4
    // This requests a temperature reading
    Wire1.beginTransmission(BMP180_ADDRESS);
    Wire1.write(0xF4);
    Wire1.write(0x2E);
    Wire1.endTransmission();

    // Wait at least 4.5ms
    delay(5);

    // Read two bytes from registers 0xF6 and 0xF7
    ut = readInt(0xF6);
    return ut;
}

// Read the uncompensated pressure value
unsigned long BMP180::readUP(){

  unsigned char msb, lsb, xlsb;
  unsigned long up = 0;

  // Write 0x34+(OSS<<6) into register 0xF4
  // Request a pressure reading w/ oversampling setting
  Wire1.beginTransmission(BMP180_ADDRESS);
  Wire1.write(0xF4);
  Wire1.write(0x34 + (OSS<<6));
  Wire1.endTransmission();

  // Wait for conversion, delay time dependent on OSS
  delay(2 + (3<<OSS));

  // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
  msb = read(0xF6);
  lsb = read(0xF7);
  xlsb = read(0xF8);

  up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);

  return up;
}


float BMP180::calcAltitude(float pressure){

  float A = pressure/101325;
  float B = 1/5.25588;
  float C = pow(A,B);
  C = 1 - C;
  C = C /0.0000225577;

  return C;
}
