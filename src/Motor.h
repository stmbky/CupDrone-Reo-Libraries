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
//    파일명     	: CupRover_Motor.h
//----------------------------------------------------------------------------
#ifndef _MOTOR_H_
#define _MOTOR_H_


#include <inttypes.h>




class Rover_Motor
{
public:
	Rover_Motor();


	void begin( void );

	void Set_Pwm( int16_t Pwm_M1, int16_t Pwm_M2 );



private:
	int16_t  Pwm_M1;
	int16_t  Pwm_M2;

	void Set_PwmOut_M1 ( uint16_t PwmData  );
	void Set_PwmOut_M2 ( uint16_t PwmData  );

	void Set_DirOut_M1 ( uint8_t DirData  );
	void Set_DirOut_M2 ( uint8_t DirData  );

};


#endif
