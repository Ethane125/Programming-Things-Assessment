#include <Zumo32U4.h>
#include <Wire.h>

//Serial1 communicates over XBee
//Serial communicates over USB cable
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
Zumo32U4Encoders encoders;
int maxSpeed = 50;
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
  //if(!start){
   // motors.setSpeeds(0,0);
  //}
  
  
  int incomingByte = 0; // for incoming serial data

  if (Serial1.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial1.read();
    //if (incomingByte == 116){
    //  start = !start;
    //  }
    switch(incomingByte){
      //61 =
      //45 -
      case 116:
        start = !start;
        if(!start){ motors.setSpeeds(0,0); }
      break;
      case 45:  //-
          maxSpeed = maxSpeed - 25;
        break;
      case 61:  //=
          maxSpeed = maxSpeed + 25;
        break;
      case 32:  //w
        motors.setSpeeds(0,0);
        break;
      case 108: //l
        turn90Left();
      break;
      case 114: //r
        turn90Right();
      break;
      case 119: //w
          motors.setSpeeds(maxSpeed,maxSpeed);
        break;
      case 100: //d

          motors.setLeftSpeed(maxSpeed*2);
          motors.setRightSpeed(((maxSpeed*2) * -1));

        break;
        case 97: //a
          motors.setRightSpeed(maxSpeed*2);
          motors.setLeftSpeed(((maxSpeed*2) * -1));

        break;
        case 115: //s

          motors.setSpeeds((maxSpeed*-1),(maxSpeed*-1));

        break;
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
  motors.setSpeeds(maxSpeed,maxSpeed);
  if(lineSensorValues[1] > centreInitial){
            Serial.println("centre line breached");
            motors.setSpeeds(0,0);
            Serial1.println("Reached a wall, Turn the zumo either left or right");
            start = false;
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

void turn90Left(){
  int16_t initialLeft = encoders.getCountsLeft();
  int16_t left = initialLeft;

  while((initialLeft + -590) < left){
    motors.setRightSpeed(maxSpeed*2);
    motors.setLeftSpeed(((maxSpeed*2) * -1));
    left = encoders.getCountsLeft();
  }
  motors.setSpeeds(0,0);
  Serial1.println("Left turn complete, swapping to auto movement");
}

void turn90Right(){
  int16_t initialRight = encoders.getCountsLeft();
  int16_t right = initialRight;

  while((initialRight + 545) > right){
    motors.setLeftSpeed(maxSpeed*2);
    motors.setRightSpeed(((maxSpeed*2) * -1));
    right = encoders.getCountsLeft();
  }
  motors.setSpeeds(0,0);
  Serial1.println("Right turn complete, swapping to auto movement");
}
