#include <Zumo32U4.h>
#include <Wire.h>

//Serial1 communicates over XBee
//Serial communicates over USB cable
Zumo32U4Motors motors;
int maxSpeed = 75;
void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  ledRed(0);
  
  
}

void loop() {
  //ledRed(0);
  // put your main code here, to run repeatedly:
  
  int incomingByte = 0; // for incoming serial data
 
  // send data only when you receive data:
  if (Serial1.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial1.read();
    
    
    switch(incomingByte){
      //61 =
      //45 -
      case 45:  //-
          maxSpeed = maxSpeed - 25;
        break;
      case 61:  //=
          maxSpeed = maxSpeed + 25;
        break;
      case 32:  //w
        motors.setSpeeds(0,0);
        ledRed(0);
        break;
      case 119: //w
        Serial1.print(maxSpeed);
        for (int speed = 0; speed <= maxSpeed; speed++) {
          motors.setSpeeds(speed,speed);
          delay(2);
        }
        break;
      case 100: //d
        for (int speed = 0; speed <= maxSpeed; speed++) {
          motors.setLeftSpeed(speed);
          motors.setRightSpeed((speed * -1));
          delay(2);
        }
        break;
        case 97: //a
        for (int speed = 0; speed <= maxSpeed; speed++) {
          motors.setRightSpeed(speed);
          motors.setLeftSpeed((speed * -1));
          delay(2);
        }
        break;
        case 115: //s
        for (int speed = 0; speed <= maxSpeed; speed++) {
          motors.setSpeeds((speed*-1),(speed*-1));
          delay(2);
        }
        break;
    }
  
//  if(incomingByte == 32){
//    motors.setSpeeds(0,0);
//    ledRed(0);
//  }
    // say what you got:
    Serial1.print("I received: ");
    Serial1.println(incomingByte, DEC);
    
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
//    if (incomingByte == 119){
//      ledRed(1);
//      for (int speed = 0; speed <= 50; speed++)
//      {
//      motors.setSpeeds(speed,speed);
//      delay(2);
//      }
//    }
  }
}
