/*
    CupDrone Library Using Example

    Made by SteamMaker & Baram

    2017.3.1
    www.steammaker.co.kr
*/

#include "LED.h"
#include "IMU.h"
#include "MSP.h"
#include "PWM.h"
#include "PID.h"


//-- 객체 생성
//
cLED     LED;
cIMU    IMU;
cMSP    MSP;
cPID    PID[3];
cPWM    PWM;

int16_t target_roll;
int16_t target_pitch;
int16_t target_yaw;
int16_t target_throtle;

//-- 모터 출력 분배
//
#define PIDMIX(X,Y,Z)  target_throtle + pid_out[ROLL]*X + pid_out[PITCH]*Y + 1 * pid_out[YAW]*Z


void setup() {
  // put your setup code here, to run once:
  LED.begin();
  MSP.begin();
  IMU.begin();
  PWM.begin();
  
  //-- 각도 제어기 게인값 설정(P, I, D)
  //
  PID[ROLL ].set_gain_angle(90, 10, 100);
  PID[PITCH].set_gain_angle(90, 10, 100);
  PID[YAW  ].set_gain_angle( 0,  0,   0);

  //-- 각속도 제어기 게인값 설정(P, I, D)
  //
  PID[ROLL ].set_gain_rate(33, 30, 23);
  PID[PITCH].set_gain_rate(33, 30, 23);
  PID[YAW  ].set_gain_rate(68, 45,  0);

  //-- 전원 On시에 가속도 센서 캘리브레이션 실시
  //   수평인 상태에서 진행해야 함
  //
  IMU.SEN.acc_cali_start();
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
  int16_t pid_out[3];
  int16_t motor_pwm[4]; 

  //-- LED
  if ( (millis() - tLed) >= 500 ) {
    tLed = millis();

    if ( MSP.Get_ArmMode() == true ) {
      LED.on();
    } else {
      LED.toggle();
    }
  }

  //-- 명령어 처리 (스마트폰으로 부터 목표 값을 받는다)
  if ( MSP.update() == true ) {
    tMsp = millis();
    target_roll    = MSP.Get_Roll();
    target_pitch   = MSP.Get_Pitch();
    target_yaw     = MSP.Get_Yaw();
    target_throtle = MSP.Get_Throtle();
  }

  tIMU = IMU.update();

  //-- 센서값 업데이트시 PID 제어 실행
  if ( tIMU > 0 ) {
    //-- PID 제어값 계산
    pid_out[ROLL ] = PID[ROLL ].update( PID_ANGLE, target_roll , IMU.angle[ROLL ], IMU.gyroData[ROLL ], tIMU );
    pid_out[PITCH] = PID[PITCH].update( PID_ANGLE, target_pitch, IMU.angle[PITCH], IMU.gyroData[PITCH], tIMU );
    pid_out[YAW  ] = PID[YAW  ].update( PID_RATE , target_yaw  , IMU.angle[YAW  ], IMU.gyroData[YAW  ], tIMU );

    //-- 모터출력 분배
    motor_pwm[REAR_R ] = PIDMIX(-1, +1, -1);   // 9
    motor_pwm[FRONT_R] = PIDMIX(-1, -1, +1);   // 10
    motor_pwm[REAR_L ] = PIDMIX(+1, +1, +1);   // 5
    motor_pwm[FRONT_L] = PIDMIX(+1, -1, -1);   // 6
  }

  for (int i = 0; i < 4; i++) {
    motor_pwm[i] = constrain(motor_pwm[i], 0, 1000);  // 더 조밀하게 제어하게 위해서 0 ~ 1000 확대시킴     
  }

  Serial.print("motor_pwm[0] :");  Serial.print(motor_pwm[0]); Serial.println("  ");
  Serial.print("motor_pwm[1] :");  Serial.print(motor_pwm[1]); Serial.println("  ");
  Serial.print("motor_pwm[2] :");  Serial.print(motor_pwm[2]); Serial.println("  ");
  Serial.print("motor_pwm[3] :");  Serial.print(motor_pwm[3]); Serial.println("  ");
}
