#include <ArduinoSTL.h>
#include <vector>
#include <string>
#include <system_configuration.h>
#include <unwind-cxx.h>
//#include <utility.h>

#include <Zumo32U4.h>
#include <Wire.h>
#include "TurnSensor.h"

//Serial1 communicates over XBee
//Serial communicates over USB cable
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4Encoders encoders;
L3G gyro;
Zumo32U4Buzzer buzzer;

int maxSpeed = 50;
#define NUM_SENSORS 3
  uint16_t lineSensorValues[NUM_SENSORS];
 uint16_t leftInitial, centreInitial, rightInitial;
 int proxFrontLeftIn, proxFrontRightIn, proxLeftLeftIn;
 bool start = false;
 bool roomFound = false;
 bool reachedJunction = false;
enum Direction {left, right};
int startPos;
std::vector<String> instructions;

struct room{
  int roomNumber;
  Direction roomDirection;
  bool objectFound;
};

//struct room rooms[3];
std::vector<room> rooms;
int roomCounter = 0;
void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  ledRed(0);
  
  lineSensors.initThreeSensors();
  proxSensors.initThreeSensors();
  lineSensors.read(lineSensorValues,true);
  leftInitial = lineSensorValues[0] + 500;
  centreInitial = lineSensorValues[0] + 50;
  rightInitial = lineSensorValues[0] + 700;
  turnSensorSetup();
  turnSensorReset();

  //while(!Serial){}
  //Serial.println(rightInitial);
}

void loop() {


  //if(!start){
   // motors.setSpeeds(0,0);
  //}
  
  //turnSensorUpdate();
  
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
      case 116: //t auto move togle
        start = !start;
        if(!start){ motors.setSpeeds(0,0); }else{
          startPos = encoders.getCountsLeft();
        }
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
        instructions.push_back(String(startPos - encoders.getCountsLeft()));
        turn90Left();
        instructions.push_back("LEFT");
        if(roomFound){
          rooms.push_back(room());
          rooms.at(roomCounter).roomDirection = left;
          searchRoom();
        }
      break;
      case 114: //r
      instructions.push_back(String(startPos - encoders.getCountsLeft()));
        turn90Right();
        instructions.push_back("RIGHT");
        if(roomFound){
          rooms.push_back(room());
          rooms.at(roomCounter).roomDirection = right;
          searchRoom();
        }
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
        case 111:
          start = false;
          motors.setSpeeds(0,0);
          roomFound = true;
        break;
        case 106:
          start = false;
          motors.setSpeeds(0,0);
          reachedJunction = true;
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
  /*int16_t initialLeft = encoders.getCountsLeft();
  int16_t left = initialLeft;

  while((initialLeft + -590) < left){
    motors.setRightSpeed(maxSpeed*2);
    motors.setLeftSpeed(((maxSpeed*2) * -1));
    left = encoders.getCountsLeft();
  }*/
  turnSensorReset();
  while(getRotationAngle() != 90){
    motors.setRightSpeed(120);
    motors.setLeftSpeed(((120) * -1));
    turnSensorUpdate();
  }
  motors.setSpeeds(0,0);
  if(!roomFound){
    Serial1.println("Left turn complete, swapping to auto movement");}
}

void turn90Right(){
  /*int16_t initialRight = encoders.getCountsLeft();
  int16_t right = initialRight;

  while((initialRight + 545) > right){
    motors.setLeftSpeed(maxSpeed*2);
    motors.setRightSpeed(((maxSpeed*2) * -1));
    right = encoders.getCountsLeft();
  }*/
  turnSensorReset();
  while(getRotationAngle() != -90){
    motors.setLeftSpeed(150);
    motors.setRightSpeed(((150) * -1));
    turnSensorUpdate();
  }
  motors.setSpeeds(0,0);
  if(!roomFound){
    Serial1.println("Right turn complete, swapping to auto movement");}
}

int32_t getRotationAngle(){
  return (((int32_t)turnAngle >> 16) * 360) >> 16;
}

void searchRoom(){
  rooms.at(roomCounter).roomNumber = roomCounter + 1;
  //String temp = "Found a room, room number: " + rooms[roomCounter].roomNumber + " and it's on the " +  rooms[roomCounter].roomDirection;
  //Serial1.print("Found a room, number: ");
  //Serial1.print(rooms[roomCounter].roomNumber);
  //Serial1.print(" and it's on the ");
  //Serial1.print(rooms[roomCounter].roomDirection);
  //Serial1.println(".");

  int16_t initialPos = encoders.getCountsLeft();
  int16_t right = initialPos;

  bool objectFound = false;

  while((initialPos + 200) > right){
    motors.setSpeeds(maxSpeed,maxSpeed);
    right = encoders.getCountsLeft();
    objectFound = checkProxSensors();
  }
  motors.setSpeeds(0,0);
  turnLeft(45);
  objectFound = checkProxSensors();
  turnRight(90);
  objectFound = checkProxSensors();
  turnLeft(45);
  
  initialPos = encoders.getCountsLeft();
  right = initialPos;
  while((initialPos - 200) < right){
    motors.setSpeeds(-maxSpeed,-maxSpeed);
    right = encoders.getCountsLeft();
  }
  motors.setSpeeds(0,0);

  if(rooms.at(roomCounter).roomDirection == 0){
    turnRight(90);
  }else{
    turnLeft(90);
  }
  rooms.at(roomCounter).objectFound = objectFound;
  if(rooms.at(roomCounter).objectFound){
    buzzer.playFrequency(440, 200, 15);
  }
  Serial1.print("Found a room, number: ");
  Serial1.print(rooms.at(roomCounter).roomNumber);
  Serial1.print(" and it's on the ");
  Serial1.print(rooms.at(roomCounter).roomDirection);
  Serial1.print(" contains object?: ");
  Serial1.print(rooms.at(roomCounter).objectFound? "1" : "0");
  Serial1.println(".");
  //if(objectFound){
  //  Serial1.println("object found in room");
  //}
  roomCounter++;
  Serial1.println("Room check complete, swapping to auto movement");
  roomFound = false;
}

void turnRight(int turn){
  turnSensorReset();
  while(getRotationAngle() != -turn){
    motors.setLeftSpeed(120);
    motors.setRightSpeed(((120) * -1));
    turnSensorUpdate();
  }
  motors.setSpeeds(0,0);
}

void turnLeft(int turn){
  turnSensorReset();
  while(getRotationAngle() != turn){
    motors.setRightSpeed(100);
    motors.setLeftSpeed(((100) * -1));
    turnSensorUpdate();
  }
  motors.setSpeeds(0,0);
}

bool checkProxSensors(){

  proxSensors.read();
  if(proxSensors.countsFrontWithLeftLeds() > 3) {return true;}
  if(proxSensors.countsFrontWithRightLeds() > 3) {return true;}

  if(proxSensors.countsLeftWithLeftLeds() > 3) {return true;}
  if(proxSensors.countsLeftWithRightLeds() > 3) {return true;}

  if(proxSensors.countsRightWithLeftLeds() > 3) {return true;}
  if(proxSensors.countsRightWithRightLeds() > 3) {return true;}

  return false;
}
