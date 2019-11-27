/*
    CupDrone Library Using Example 
    
    Made by SteamMaker & Baram 

    2017.3.1    
    www.steammaker.co.kr 
*/

#include "LED.h"
#include "MSP.h"

cLED    LED;
cMSP	MSP;

void setup() {
  // put your setup code here, to run once:
  LED.begin();
  MSP.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  static uint32_t tLed;

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
}
