#include <Zumo32U4.h>
#include <Wire.h>

//Serial1 communicates over XBee
//Serial communicates over USB cable
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
int maxSpeed = 75;
#define NUM_SENSORS 3
  uint16_t lineSensorValues[NUM_SENSORS];
 uint16_t leftInitial, centreInitial, rightInitial;
void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  ledRed(0);
  
  lineSensors.initThreeSensors();
  lineSensors.read(lineSensorValues,true);
  leftInitial = lineSensorValues[0] + 500;
  centreInitial = lineSensorValues[0] + 50;
  rightInitial = lineSensorValues[0] + 700;
  while(!Serial){}
  Serial.println(rightInitial);
}

void loop() {
  //ledRed(0);
  // put your main code here, to run repeatedly:
  
  int incomingByte = 0; // for incoming serial data
  lineSensors.read(lineSensorValues,true);
  //Serial.println(lineSensorValues[0]);
  //Serial.println(lineSensorValues[1]);
  //Serial.println(lineSensorValues[2]);


  if(lineSensorValues[0] > leftInitial){
            Serial.println("left line breached");
          }
  if(lineSensorValues[1] > centreInitial){
            Serial.println("centre line breached");
          }
  if(lineSensorValues[2] > rightInitial){
            Serial.println("right line breached");
          }
  
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
      case 32:  // ' '
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
        case 116: //t auto move
          if(lineSensorValues[0] > 200){
            Serial.println("left line breached");
          }
          if(lineSensorValues[1] > 200){
            Serial.println("centre line breached");
          }
          if(lineSensorValues[2] > 200){
            Serial.println("right line breached");
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
