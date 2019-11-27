/*
    CupDrone Library Using Example 
    
    Made by SteamMaker & Baram 

    2017.3.1    
    www.steammaker.co.kr 
*/

#include "LED.h"

cLED     LED;

void setup() {
  // put your setup code here, to run once:
  LED.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  LED.on();
  delay(1000);
  LED.off();
  delay(1000);
}
