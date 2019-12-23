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
 bool start = false;

 
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
  if(!start){
    motors.setSpeeds(0,0);
  }
  //ledRed(0);
  // put your main code here, to run repeatedly:
  
  int incomingByte = 0; // for incoming serial data

  if (Serial1.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial1.read();
    if (incomingByte == 116){
      start = !start;
      }

  }
  if(start){

  static uint16_t lastSampleTime = 0;
  if ((uint16_t)(millis() - lastSampleTime) >= 150)
  {
    lastSampleTime = millis();

    
    lineSensors.read(lineSensorValues, true);

    move();
  }
    
    
    }
  
  
  
  
}

void move(){
  lineSensors.read(lineSensorValues,true);
  //Serial.println(lineSensorValues[0]);
  //Serial.println(lineSensorValues[1]);
  //Serial.println(lineSensorValues[2]);
  motors.setSpeeds(50,50);
  if(lineSensorValues[1] > centreInitial){
            Serial.println("centre line breached");
            motors.setSpeeds(0,0);
          }else{
            if(lineSensorValues[0] > leftInitial){
            Serial.println("left line breached");
            adjustRight();
          }
  
  if(lineSensorValues[2] > rightInitial){
            Serial.println("right line breached");
            adjustLeft();
          }
            }
  
  }

void adjustRight(){
  motors.setRightSpeed(-100);
  motors.setLeftSpeed(100);
}

void adjustLeft(){
  motors.setRightSpeed(100);
  motors.setLeftSpeed(-100);
  }
