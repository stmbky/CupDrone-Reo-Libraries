/*
    CupDrone Library Using Example 
    
    Made by SteamMaker & Baram 

    2017.3.1    
    www.steammaker.co.kr 
*/

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
      
}

void loop() {
  if(Serial1.available()) {
    uint8_t mspData = Serial1.read();    
    Serial.print((char)mspData);
    Serial.print('\t');
    Serial.println(mspData, DEC);
  }
}

