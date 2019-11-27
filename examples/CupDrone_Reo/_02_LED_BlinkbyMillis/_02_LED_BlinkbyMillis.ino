/*
    CupDrone Library Using Example 
    
    Made by SteamMaker & Baram 

    2017.3.1    
    www.steammaker.co.kr 
*/

#include "LED.h"

cLED    LED;  //객체 선언


void setup() {
  // put your setup code here, to run once:
  LED.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  static uint32_t tLed;

  if( (millis() - tLed) >= 1000)
  {
    tLed = millis();
    
    LED.on();
    delay(100);
  }
  
  LED.off();  
  
}
