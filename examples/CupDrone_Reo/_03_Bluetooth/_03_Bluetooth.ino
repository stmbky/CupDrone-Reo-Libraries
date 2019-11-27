/*
    CupDrone Library Using Example 
    
    Made by SteamMaker & Baram 

    2017.3.1    
    www.steammaker.co.kr 
*/

void setup()
{
  Serial.begin(9600);     // MPU 와  PC 간의 통신속도 
  Serial1.begin(115200);  // MPU 와  블루투스간의 통신 속도 
}

void loop()
{
  // Serial –> Data –> Serial1
  if (Serial.available()) {
    Serial1.write(Serial.read());
  }
  
  // Serial1 –> Data –> Serial
  if (Serial1.available()) {
    Serial.write(Serial1.read());
  }

  
}
