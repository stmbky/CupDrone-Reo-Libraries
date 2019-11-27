/*
    CupDrone Library Using Example 
    
    Made by SteamMaker & Baram 

    2017.3.1    
    www.steammaker.co.kr 
*/

#include "I2C.h"
#include "MPU6050.h"

cMPU6050  MPU6050;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  MPU6050.gyro_init();
  MPU6050.acc_init();  
}

void loop() {
  // put your main code here, to run repeatedly:

  MPU6050.acc_get_adc();
  MPU6050.gyro_get_adc();
  
  Serial.print("accRoll :");  Serial.print(MPU6050.accADC[0]);  Serial.print(" ");
  Serial.print("accPitch :"); Serial.print(MPU6050.accADC[1]);  Serial.print(" ");
  Serial.print("accYaw :");   Serial.print(MPU6050.accADC[2]);  Serial.print(" ");
  Serial.print("gyroRoll :");  Serial.print(MPU6050.gyroADC[0]); Serial.print(" ");
  Serial.print("gyroPitch :"); Serial.print(MPU6050.gyroADC[1]); Serial.print(" ");
  Serial.print("gyroYaw :");   Serial.print(MPU6050.gyroADC[2]); Serial.println(" ");
    
}
