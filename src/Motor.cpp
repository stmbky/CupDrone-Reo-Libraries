//----------------------------------------------------------------------------
//    프로그램명 	: CupRover
//
//    만든이     	: Cho Han Cheol & SteamMaker
//
//    날  짜     :
//
//    최종 수정  	:
//
//    MPU_Type	:
//
//    파일명     	: CupRover_Motor.cpp
//----------------------------------------------------------------------------



#include <avr/interrupt.h>
#include <Arduino.h>

#include "Motor.h"



// M1 (Left Motor)
#define M1_PIN_DIR_FW     4     // forward
#define M1_PIN_DIR_BW     7     // backward
#define M1_PIN_PWM        5

// M2 (Right Motor)
#define M2_PIN_DIR_FW    9    // forward
#define M2_PIN_DIR_BW    12   // backward
#define M2_PIN_PWM       6




#define MOTOR_FW		0
#define MOTOR_BW		1
#define MOTOR_RW        2
#define MOTOR_LW        3
#define MOTOR_STOP	    4






/*---------------------------------------------------------------------------
     TITLE   : Rover_Motor
     WORK    :
     ARG     : void
     RET     : void
  ---------------------------------------------------------------------------*/
Rover_Motor::Rover_Motor()
{
  Pwm_M1  = 0;
  Pwm_M2  = 0;
}





/*---------------------------------------------------------------------------
     TITLE   : begin
     WORK    :
     ARG     : void
     RET     : void
  ---------------------------------------------------------------------------*/
void Rover_Motor::begin()
{
  //-- I/O 초기화
  //
  pinMode( M1_PIN_DIR_FW, OUTPUT );
  pinMode( M1_PIN_DIR_BW, OUTPUT );
 
  pinMode( M2_PIN_DIR_FW, OUTPUT );
  pinMode( M2_PIN_DIR_BW, OUTPUT );
  
  Set_DirOut_M1 ( MOTOR_STOP );
  Set_DirOut_M2 ( MOTOR_STOP );

  Set_PwmOut_M1 ( 0 );
  Set_PwmOut_M2 ( 0 );
}





/*---------------------------------------------------------------------------
     TITLE   : Set_PwmOut_M1
     WORK    :
     ARG     : void
     RET     : void
  ---------------------------------------------------------------------------*/
void Rover_Motor::Set_Pwm( int16_t Pwm_M1, int16_t Pwm_M2 )
{
  if ( Pwm_M1 >  255 ) Pwm_M1 =  255;
  if ( Pwm_M1 < -255 ) Pwm_M1 = -255;

  if ( Pwm_M2 >  255 ) Pwm_M2 =  255;
  if ( Pwm_M2 < -255 ) Pwm_M2 = -255;


  if ( Pwm_M1 == 0 )
  {
    Set_DirOut_M1 ( MOTOR_STOP );
    Set_PwmOut_M1 ( 0 );
  }
  else if ( Pwm_M1 > 0 )
  {
    Set_DirOut_M1 ( MOTOR_FW );
    Set_PwmOut_M1 ( Pwm_M1);
  }
  else
  {
    Set_DirOut_M1 ( MOTOR_BW );
    Set_PwmOut_M1 ( -Pwm_M1 );
  }


  if ( Pwm_M2 == 0 )
  {
    Set_DirOut_M2 ( MOTOR_STOP );
    Set_PwmOut_M2 ( 0 );
  }
  else if ( Pwm_M2 > 0 )
  {
    Set_DirOut_M2 ( MOTOR_FW );
    Set_PwmOut_M2 ( Pwm_M2 );
  }
  else
  {
    Set_DirOut_M2 ( MOTOR_BW );
    Set_PwmOut_M2 ( -Pwm_M2 );
  }
}





/*---------------------------------------------------------------------------
     TITLE   : Set_PwmLeftOut
     WORK    :
     ARG     : void
     RET     : void
  ---------------------------------------------------------------------------*/
void Rover_Motor::Set_PwmOut_M1 ( uint16_t PwmData  )
{
  if ( PwmData > 255 ) PwmData = 255;

  Pwm_M1 = PwmData;

  analogWrite( M1_PIN_PWM, PwmData );
}





/*---------------------------------------------------------------------------
     TITLE   : Set_PwmRighttOut
     WORK    :
     ARG     : void
     RET     : void
  ---------------------------------------------------------------------------*/
void Rover_Motor::Set_PwmOut_M2 ( uint16_t PwmData  )
{
  if ( PwmData > 255 ) PwmData = 255;

  Pwm_M2 = PwmData;

  analogWrite( M2_PIN_PWM, PwmData );
}





/*---------------------------------------------------------------------------
     TITLE   : Set_DirLeftOut
     WORK    :
     ARG     : void
     RET     : void
  ---------------------------------------------------------------------------*/
void Rover_Motor::Set_DirOut_M1( uint8_t DirData  )
{
  switch ( DirData )
  {
    case MOTOR_FW:
      digitalWrite( M1_PIN_DIR_FW, LOW );
      digitalWrite( M1_PIN_DIR_BW, HIGH);
      break;

    case MOTOR_BW:
      digitalWrite( M1_PIN_DIR_FW, HIGH );
      digitalWrite( M1_PIN_DIR_BW, LOW );
      break;

    case MOTOR_STOP:
      digitalWrite( M1_PIN_DIR_FW, LOW );
      digitalWrite( M1_PIN_DIR_BW, LOW );
      break;

    default:
      digitalWrite( M1_PIN_DIR_FW, LOW );
      digitalWrite( M1_PIN_DIR_BW, LOW );
      break;
  }
}





/*---------------------------------------------------------------------------
     TITLE   : Set_DirRightOut
     WORK    :
     ARG     : void
     RET     : void
  ---------------------------------------------------------------------------*/
void Rover_Motor::Set_DirOut_M2( uint8_t DirData  )
{
  switch ( DirData )
  {
    case MOTOR_FW:
      digitalWrite( M2_PIN_DIR_FW, LOW );
      digitalWrite( M2_PIN_DIR_BW, HIGH );
      break;

    case MOTOR_BW:
      digitalWrite( M2_PIN_DIR_FW, HIGH);
      digitalWrite( M2_PIN_DIR_BW, LOW );
      break;

    case MOTOR_STOP:
      digitalWrite( M2_PIN_DIR_FW, LOW );
      digitalWrite( M2_PIN_DIR_BW, LOW );
      break;

    default:
      digitalWrite( M2_PIN_DIR_FW, LOW );
      digitalWrite( M2_PIN_DIR_BW, LOW );
      break;
  }
}


