#include <ArduinoSTL.h>
#include <vector>
#include <string>
#include <system_configuration.h>
#include <unwind-cxx.h>

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

int maxSpeed = 70;
#define NUM_SENSORS 3
  uint16_t lineSensorValues[NUM_SENSORS];
 uint16_t leftInitial, centreInitial, rightInitial;
 int proxFrontLeftIn, proxFrontRightIn, proxLeftLeftIn; //this sets up the 3 line sensors and the 3 prox sensors
 bool start = false;  //this boolean is used to determin whether or not automove is active
 bool roomFound = false; 
 bool reachedJunction = false;
enum Direction {left, right}; 
int startPos;

int roomCounter = 0;

/*
These are all the classes that are used to store the instructions that the zumo follows
*/
class Instruction {
protected:
  std::string type;
public:
  Instruction() {}
  std::string getType() { return type; }
};

class Turn : public Instruction {
protected:
  std::string direction;
public:
  Turn(std::string direction) : direction(direction) { type = "turn"; }
  std::string getDirection() { return direction; }
};

class Straight : public Instruction {
protected:
  int distance;
public:
  Straight(int distance) : distance(distance) { type = "straight"; }
  int getDistance() { return distance; }
};

class Room : public Instruction {
protected:
  int roomID;
  bool objectFound;
  std::string direction;
public:
  Room(int roomID, std::string direction) : roomID(roomID), direction(direction) { type = "room"; }
  std::string getDirection() { return direction; }
  bool getFound() { return objectFound; }
  int getRoomID() { return roomID; }
  void setObjectFound(bool found) { objectFound = found; }
};

class TJunction : public Instruction {
protected:
  std::string direction;
public:
  TJunction(std::string direction) : direction(direction) { type = "TJunction"; }
  std::string getDirection() { return direction; }
};
class EndofTJunc : public Instruction {
public:
  EndofTJunc() { type = "endTJunc"; }
};
class StartofTJunc : public Instruction {
public:
  StartofTJunc() { type = "startTJunc"; }
};
class StartInsrct : public Instruction {
public:
  StartInsrct() { type = "start"; }
};
//a vector of instruction pointers
std::vector<Instruction*> instructions;



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
  instructions.push_back(new StartInsrct());  
}//all the sensors are initilised and the start instriction object is pushed to the vector

void loop() {
  
  int incomingByte = 0; // for incoming serial data

  if (Serial1.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial1.read();
    switch(incomingByte){
      //61 =
      //45 -
      case 116: 
      //t auto move toggle, also sets the counter for the straight
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
      case 32:  // space character
        motors.setSpeeds(0,0);
        break;
      case 108: 
      //l 90 degrees left, pushes back the straight
        instructions.push_back(new Straight(encoders.getCountsLeft() - startPos));
        if(reachedJunction){
          instructions.push_back(new TJunction("left"));  //if its a junction push the junction object instead of a turn
          turn90Left();
          reachedJunction = false;
        }else{
            if(roomFound){
            turnLeft(90);
            Room *room = new Room((roomCounter + 1), "left"); //if its a turn into a room create a room object set the direction and its id then search the room
            searchRoom(room);
          }else{
            turn90Left();
            instructions.push_back(new Turn("left"));
          }
        }
      break;
      case 114: 
      //r 90 degrees right, pushes back the straight
        instructions.push_back(new Straight(encoders.getCountsLeft() - startPos));
         if(reachedJunction){
          instructions.push_back(new TJunction("right"));
          turn90Right();
          reachedJunction = false;
        }else{
            if(roomFound){
            turnRight(90);
            Room *room = new Room((roomCounter + 1), "right");
            searchRoom(room);
          }else{
            turn90Right();
            instructions.push_back(new Turn("right"));
          }
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

          motors.setSpeeds((maxSpeed*-1),(maxSpeed*-1));  //these four commands are the basic movement

        break;
        case 111: //room found button
          start = false;
          motors.setSpeeds(0,0);  
          roomFound = true;
        break;
        case 106: //reached junction button
          start = false;
          motors.setSpeeds(0,0);
          reachedJunction = true;
        break;
        case 121: //y end of tjunc
          instructions.push_back(new Straight(encoders.getCountsLeft() - startPos));
          instructions.push_back(new EndofTJunc());
          endOfTJunction();
        break;
        case 101: //e end of map
          instructions.push_back(new Straight(encoders.getCountsLeft() - startPos));
          //instructions.push_back(new EndofTJunc());
          goHome();
        break;
    }

  }
  if(start){
  //if auto move is active every 150ms it will call the move fucntion
  static uint16_t lastSampleTime = 0;
  if ((uint16_t)(millis() - lastSampleTime) >= 150)
  {
    lastSampleTime = millis();

    
    lineSensors.read(lineSensorValues, true);

    move();
  }
    
    
    }
  
}
/*
 The move function checks the line sensors with the centre sensor taking priority
 because this means that the zumo has hit a turn
 then the left and right sensors trigger adjustments
*/
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
  motors.setRightSpeed(-70);
  motors.setLeftSpeed(70);
}

void adjustLeft(){
  motors.setRightSpeed(70);
  motors.setLeftSpeed(-70);
  }
//turn90left/right use the gyro to move whilst the angle is not 90
void turn90Left(){
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
/*
when search room is called it moves into the room and does a spin
all whilst checking the prox sesnors, if true then it beeps and
sets the object found in the room object and pushes it back to the vector
*/
void searchRoom(Room *room){

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
 String temp = room->getDirection().c_str();
  if( temp == "left"){
    turnRight(90);
  }else{
    turnLeft(90);
  }
  room->setObjectFound(objectFound);
  if(objectFound){
    buzzer.playFrequency(440, 200, 15);
  }
  Serial1.print("Found a room, number: ");
  Serial1.print(String(room->getRoomID()));
  Serial1.print(" and it's on the ");
  Serial1.print((room->getDirection().c_str() == "right"? "1" : "0"));
  Serial1.print(" contains object?: ");
  Serial1.print(room->getFound()? "1" : "0");
  Serial1.println(".");
  //if(objectFound){
  //  Serial1.println("object found in room");
  //}
  instructions.push_back(room);
  roomCounter++;
  Serial1.println("Room check complete, swapping to auto movement");
  roomFound = false;
}
/*
does a 180 then loops back through the list of instructions until
the start of the T junction and executes any straights
It does this by casting it to the correct object then getting the distance
*/
void endOfTJunction(){
  //Serial.println(instructions.size());
  for(int i = 0; i < instructions.size(); i++){
    Serial.println(instructions.at(i)->getType().c_str());
  }
  Serial.println("-----");
  turnLeft(90);
  turnLeft(90);
  int index = instructions.size() - 2;
  String temp = instructions.at(index)->getType().c_str();
  while(temp != "TJunction"){
     Serial.println(instructions.at(index)->getType().c_str());
    if(temp == "room"){
      //index = index - 1;
      Serial.println("ROOM FOUND");
    }else{
      Straight *s = static_cast<Straight*>(instructions.at(index));
      Serial.println(s->getDistance());
      movefwd(s->getDistance());
    }
    index = index - 1;
    temp = instructions.at(index)->getType().c_str();
  }
  Serial1.println("Reached T junction");
  instructions.push_back(new StartofTJunc());
}
/*
This functions the same as endOfTJunction() however it has alot more conditions
the main one being a T junction, it has to check wether there is a room and if it has an object in
if true then loop to the start of the T junction and execute the same instructions, this will get you
to the enterence of the room you can then scan the room and work backwards again to get back to the
start of the T junction
*/
void goHome(){
  turnLeft(90);
  turnLeft(90);

//for(int i = 0; i < instructions.size(); i++){
//    Serial1.println(instructions.at(i)->getType().c_str());
//  }
 // Serial1.println("-----");
  
  int index = instructions.size() - 1;
  String temp = instructions.at(index)->getType().c_str();

  while(temp != "start"){
    //Serial1.println(temp);
    
    if(temp == "startTJunc"){
      //Serial1.println("hit T Junc ===========");
      bool researchedRoom = false;
      int juncIndex = index - 1;
      String juncType = instructions.at(juncIndex)->getType().c_str();
      while(juncType != "TJunction"){
        //Serial1.println(juncType);
        if(juncType == "room"){
          //Serial1.println("HIT room ===========");
          Room *room = static_cast<Room*>(instructions.at(juncIndex));
          if(room->getFound()){
            //Serial1.println("object in room======");
            while(juncType != "TJunction"){
              juncIndex = juncIndex - 1;
              juncType = instructions.at(juncIndex)->getType().c_str();
            }
           // Serial1.println(instructions.at(juncIndex)->getType().c_str());
            juncIndex = juncIndex + 1;
            //Serial1.println(instructions.at(juncIndex)->getType().c_str());
            Straight *s = static_cast<Straight*>(instructions.at(juncIndex));
            movefwd(s->getDistance());
            juncIndex = juncIndex + 1;
            //Serial1.println(instructions.at(juncIndex)->getType().c_str());
            scanRoomAgainTJunc(room->getDirection().c_str());
            juncIndex = juncIndex - 1;
            //Serial1.println(instructions.at(juncIndex)->getType().c_str());
            movefwd(s->getDistance());
            researchedRoom = true;
          }
        }
        juncIndex = juncIndex - 1;
        juncType = instructions.at(juncIndex)->getType().c_str();
      }
      //Serial1.println(instructions.at(juncIndex)->getType().c_str());
      TJunction *j = static_cast<TJunction*>(instructions.at(juncIndex));
      String juncDirec = j->getDirection().c_str();
      if(researchedRoom){ //depending on if you have come from a room or not turns you back into the main coridoor
        if(juncDirec == "left"){
          turnRight(90);
        }else{
          turnLeft(90);
        }
      }else{
        if(juncDirec == "left"){
          turnLeft(90);
        }else{
          turnRight(90);
        }
      }
      index = juncIndex;
    }

    if(temp == "straight"){
      //Serial1.println("hit straight");
      Straight *s = static_cast<Straight*>(instructions.at(index));
      movefwd(s->getDistance());
    }

    
    if(temp == "turn"){
      //Serial1.println("hit turn");
      Turn *t = static_cast<Turn*>(instructions.at(index));
      String direc = t->getDirection().c_str();
      if(direc == "left"){ turnRight(90); }
      else{ turnLeft(90); }
    }

    if(temp == "room"){
      //Serial1.println("hit room");
      Room *room = static_cast<Room*>(instructions.at(index));
      if(room->getFound()){
        scanRoomAgain(room->getDirection().c_str());
      }
    }
    
    index = index - 1;
    temp = instructions.at(index)->getType().c_str();
  }
   ledRed(0);
   ledYellow(0);
   ledGreen(0);
   buzzer.stopPlaying();
}
/*
These two room commands are the same exept when you search a room on a T junction
you want to turn back the way you came but on a regular room you want to continue on
the code is the same as scanRoom but this time if an object is found it plays a tone
and turns the LEDs on
*/
void scanRoomAgainTJunc(String directionRoom){
  if(directionRoom == "left"){
          turnLeft(90);
        }else{
          turnRight(90);
        }

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

          if(objectFound){
              ledRed(1);
              ledYellow(1);
              ledGreen(1);
              buzzer.playFrequency(440, 300000, 10); //5 minutes
          }
      
         if(directionRoom == "left"){
          turnLeft(90);
        }else{
          turnRight(90);
        }
}

void scanRoomAgain(String directionRoom){
  if(directionRoom == "left"){
          turnRight(90);
        }else{
          turnLeft(90);
        }
        

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

          if(objectFound){
              ledRed(1);
              ledYellow(1);
              ledGreen(1);
              buzzer.playFrequency(440, 300000, 10); //5 minutes
          }


         if(directionRoom == "left"){
          turnLeft(90);
        }else{
          turnRight(90);
        }
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
/*
this method moves forward a set distance based on the encoder value passed in
it has a dely on the turn sensor so that it has 100ms to turn in
before the straight movemnt in the while loop takes over
*/
void movefwd(int distance){
  int16_t initialPos = encoders.getCountsLeft();
  int16_t left = initialPos;
  while((initialPos + distance) > left){
    lineSensors.read(lineSensorValues,true);
    if(lineSensorValues[1] > centreInitial){break;}
    else{
      if(lineSensorValues[0] > leftInitial){ adjustRight(); delay(100); }
      if(lineSensorValues[2] > rightInitial){ adjustLeft(); delay(100); }
      }
    motors.setSpeeds(maxSpeed,maxSpeed);
    left = encoders.getCountsLeft();
  }
  motors.setSpeeds(0,0);
}
