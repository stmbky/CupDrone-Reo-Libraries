/*
    CupDrone Library Using Example

    Made by SteamMaker & Baram

    2017.3.1
    www.steammaker.co.kr
*/

#include "I2C.h"
#include "SRF02.h"


cSRF02    SONAR;

int16_t target_distance;


void setup() {
  // put your setup code here, to run once:
  I2C.begin();
  SONAR.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  static uint32_t tTime;

  if ( Serial.available() )
  {
    char Ch = Serial.read();

    if ( Ch == 'd' )
    {
      while (1)
      {
        SONAR.update();

        if ( (millis() - tTime) >= 100 )
        {
          tTime = millis();
          Serial.print("SONA : ");
          Serial.print(SONAR.distance);
          Serial.println(" cm");
        }

        if ( Serial.available() )
        {
          if ( Serial.read() == 'x' ) break;
        }
      }
    }
  }
}
