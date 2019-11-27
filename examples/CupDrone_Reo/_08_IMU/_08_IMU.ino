/*
    CupDrone Library Using Example

    Made by SteamMaker & Baram

    2017.3.1
    www.steammaker.co.kr
*/

#include "LED.h"
#include "MSP.h"
#include "IMU.h"

cLED  LED;
cMSP  MSP;
cIMU  IMU;

int16_t target_roll;
int16_t target_pitch;
int16_t target_yaw;
int16_t target_throtle;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  LED.begin();
  MSP.begin();
  IMU.begin();

  // 전원이 On시에 가속도 센서 캘리브레이션 실시
  // 수평인 상태에서 진행해야 함
  IMU.SEN.acc_cali_start();      // MPU6050 의 객체를 SEN 으로 표시 -> MPU6050.acc_cali_start()
  while ( IMU.SEN.acc_cali_get_done() == false )
  {
    IMU.update();
    LED.toggle();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  static uint32_t tLed;
  static uint32_t tMsp;
  uint16_t tIMU;

  //-- LED
  //
  if ( (millis() - tLed) >= 500 ) {
    tLed = millis();

    if ( MSP.Get_ArmMode() == true ) {
      LED.on();
    } else {
      LED.toggle();
    }
  }

  //-- 명령어 처리
  if ( MSP.update() == true )
  {
    tMsp = millis();
    target_roll    = MSP.Get_Roll();
    target_pitch   = MSP.Get_Pitch();
    target_yaw     = MSP.Get_Yaw();
    target_throtle = MSP.Get_Throtle();

    //-- ARM모드가 아니면 모터 정지
    if ( MSP.Get_ArmMode() == false )
    {
      target_roll    = 0;
      target_pitch   = 0;
      target_yaw     = 0;
      target_throtle = 0;
    }
  }

  //-- 센서값 업데이트(200Hz)
  //
  tIMU = IMU.update();


  //-- 센서값 업데이트시 PID 제어 실행
  //
  if ( tIMU > 0 )
  {
    Serial.print("angleRoll :");  Serial.print(IMU.angle[ROLL]);  Serial.print(" ");
    Serial.print("anglePitch :"); Serial.print(IMU.angle[PITCH]);  Serial.print(" ");
    Serial.print("angleYaw :");   Serial.println(IMU.angle[YAW]);
  }
}
