/*
    CupDrone Library Using Example 
    
    Made by SteamMaker & Baram 

    2017.3.1    
    www.steammaker.co.kr 
*/

#include "LED.h"
#include "MSP.h"

cLED    LED;
cMSP  MSP;

int16_t target_roll;
int16_t target_pitch;
int16_t target_yaw;
int16_t target_throtle;

void setup() {
  // put your setup code here, to run once:
  LED.begin();
  MSP.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  static uint32_t tLed;
  static uint32_t tMsp;
  
  if( (millis() - tLed) >= 500)
  {
    tLed = millis();

    if(MSP.Get_ArmMode() == true) {
      LED.on();
    }
    else {
      LED.toggle();
    }
  }

  if( MSP.update() == true )
  {
    tMsp = millis();
    target_roll    = MSP.Get_Roll();
    target_pitch   = MSP.Get_Pitch();
    target_yaw     = MSP.Get_Yaw();
    target_throtle = MSP.Get_Throtle();
  }

  Serial.print("Roll :");    Serial.print( target_roll );     Serial.print( "\t" );
  Serial.print("Pitch :");   Serial.print( target_pitch );     Serial.print( "\t" );
  Serial.print("YAW :");     Serial.print( target_yaw );       Serial.print( "\t" );
  Serial.print("Throttle :");Serial.println( target_throtle );   
}
