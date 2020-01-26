# Programming Things Assessment

This readme will outline how I approched and solved each task and any issues I faced during the development of this task.

[This is a link to a video of the zumo completing my track at home](https://drive.google.com/file/d/15f01JPs-H_MuNmD9MYKVrN4pQqrjuo-2/view?usp=sharing)

*If the video doesn't play, try incognito or another browser or download it.*

## Task 1 - Manual control of the Zumo
To achieve this task, I created a basic C# UI that had 5 buttons on it, forward, reverse, right, left and stop. each one of these buttons sent a character over the com port that the xbee receiver was on.

The zumo had a switch statement and for each character preformed the appropriate action. It was just basic setting the motor speed to either a positive 
## Task 2 - Autonomous control of the Zumo
For this task I added a new button to the UI for autonomous movement, all this button does is send another character to the zumo.

For the zumo I added a new condition to the switch statement that set a Boolean to whatever value it was not `start = !start`, this allowed the auto movement to act as a toggle, when start is true every 150ms it calls the `move()` function this sets the motors to go forward and preforms a check to make sure the left, centre or right line sensors haven’t been breached. I had to make the thresholds for the left and right sensor higher because if not they would trigger before the centre sensor did meaning that it would try and adjust left/right if it hit a straight wall. When the centre sensor is hit it stops the zumo, `start = false` and sets speed to 0.
The adjust function is just a turn but due to the 150ms delay on the move function it means it turns slightly left or right for 150ms allowing the zumo to turn back to towards the corridor.
## Task 3 - Turning Corners
For this I added 2 new buttons to the UI turn 90° left and turn 90° right.

When either of these characters is received it calls a function that turns the zumo either left or right. At this stage I used the encoders to calculate when it had done a 90° turn but later on in task 4, I changed it to instead use the gyro.
## Task 4 - The Zumo turns autonomously around a corner
At this stage I implemented a method in the UI that would receive the messages on the serial port and add them to a text box on the UI. I used it to complete this task, so when the 90° turn had been completed it would send a message on the serial port saying, "turn complete, swapping back to auto movement". When this message is received by the UI it then sends the auto move character back to the zumo so it starts moving autonomously.

I swapped the zumo from using the encoders to turn to the gyro. I used Turnsensor.h and TurnSensor.cpp that were used in the zumo examples to get the values from the gyro sensor. I swapped to using the gyro because it proved to be more consistent at providing a near to 90° turn.
## Task 5 - The Zumo searches a room
I added a new button to the UI called room this sent a new character to the UI, It also enables the 90° turn buttons so you can specify which direction the room is in.

When the room character is received it changes a Boolean called `roomFound` to true then when the character for a turn comes in it preforms the turn but then also calls the function `searchRoom` This function moves the zumo forward a little bit turns 45° in each direction whilst it does this it scans for an object using its proximity sensors it calls the function `checkProxSensors()`. This returns a Boolean of whether it found something, then finally reverses and turns back to the direction it was facing.

However, this data also needs to be stored so I created a struct called room that contained the direction the room was in, it's room ID and if it had an object in or not. I then created a array of these structs to store all the data for a room. I also send a string back to the UI over the serial port `Found a room, number: roomID and it's on the (0 or 1 for left and right)  contains object?: (0 or 1)` then in the UI I regex this message to get the roomID, Direction and containsObject then I populate another text box with this information so you can see it in the UI.

At this point I decided that storing the room structs in a fixed size array was not a good method as even though there probably would never be more than 10 rooms it was a messy solution. So I added the `ArduinoSTL` library and that allows me to use the standard templates from c++, this allowed me to use a vector of structs so I could use `.push_back()` to add a new room to the collection.

When it comes to using the proximity sensors I have noticed an issue, the sensitivity of the sensor is dependent on the batteries, They are more sensitive when they are fresh, This has caused me some issues but I didn't figure it out until now so I have been unable to work around it, e.g. when they are new it could pick up objects in other rooms. I think the light levels of the room also effect the sensitivity.

## Task 6 - The T-junction
For this task I added 2 new buttons to the UI, one for signalling that the zumo had reached a T-junction and another to signal that it had reached the end of a t junction.

thinking about this task and task 7 I knew I had to implement some way of storing every instruction that the zumo had completed so that once it reaches the end of the junction it can retrace its steps and ignore a room if there was one. So, I changed the implementation of storing rooms yet again. This time I used classes, I created a base class called instruction that had one protected attribute that was the instruction type and one method to get this type. I then created derived classes from instruction for a room this class sets the type to 'room' and then stores all the same data it did when it was a struct(direction,ID,objectFound), I also created classes for Straight this sets type to 'straight' and has an attribute called distance, I also created classes for T-junction which stored direction and t Junction end which signalled the end of the T-junction.

I then created a vector of pointers of instructions. This means that I can push back a pointer to any of these derived classes, so this let me build a vector of all the instructions that had been made, so then based on whatever button is pressed on the UI the appropriate instruction is carried out but it is also stored in the vector of instructions. for example whenever the auto toggle for movement is called it stores the current encoder value then whenever the turn function is called it takes that value away from the current encoder value and stores it in the vector as a straight `instructions.push_back(new Straight(encoders.getCountsLeft() - startPos));` and then it will push back its direction it turned `instructions.push_back(new Turn("right"));`. the same happens for the room object too.

This then allowed me to create a method called `endOfTJunction()` that first turns the zumo 180° then loops backwards through the vector until it gets to the start of the T-junction and if any of the instruction types equal 'straight' then downcast the instruction to Straight then get the distance and move for that distance on the encoder.

## Task 7 - The return journey
I had done most of the groundwork for this task in the previous task as automatically leaving the T-junction will function the same as automatically getting back to the start. All it required for more conditions to check for different scenarios. I added one new button to the UI to signal that it was time to return home.

Once this character is received I call a method called `goHome()` this turns the zumo 180° then loops back through the instruction vector until it reaches the start type (this is an object I add just to indicate the start of the map). It then has a check for each of the instruction derived classes. so, for straight it casts it to the straight object then gets the distance and moves that much. for a turn it reverses the direction and executes it. For a room it checks wither foundObject is true if not it can skip the instruction but if there is an object then it calls a new method that rescans the room, this time it doesn't create a room object but if the room is still full it plays a tone and turns the LEDs on then continues to the next instruction.

If the type is equal to the end of a T junction then it has to create another loop to check if there is a room within the two T junction instructions(start and end) and if there is and the room is not empty then it executes the straight instruction to get to the room then rescans the room then turns back the way it came and then executes the straight again once it has got to that point it then skips to the T junction command so it will skip the rest of the T junction. If the T junction had no room, then it skips to the end of the T junction and executes the inverse of the turn then continues.


## Acknowledgments

Turnsensor.h and TurnSensor.cpp

I included these files for controlling the gyroscope, they are from the example code provided by the zumo library.
I use them to set the gyroscope to 0 then retrieve the gyroscope value so I can tell when the z coordinate has reached a certain angle to achieve turning.

[ArduinoSTL by Mike Matera](https://github.com/mike-matera/ArduinoSTL)

I used this library so I could use the standard c++ libraries such as std::vector and std::string




