### 03/05
- Created design for base
- Printed base
- Printing of base failed (fell over in the printer)

### 04/05
- Team meeting to prepare and finish AVC plan

### 05/05 12.20
- Discussed methods in code and general 
- Created outline of methods
- Josh wrote goForward
- Josh created makefile
- Changed GitHub to use one branch
- Ben wrote turnLeft
- Penny improved plan
- Josh wrote detectLine
- Toby wrote detectLineToby
- Josh wrote turnRight
- Josh wrote pivotLeft

### 07/05 
- Ben attached the poles connecting the motherboards
- Ben attached the base to the motherboards
- Ben attached the left and right wheels to the base
- The camera was connected to the top base
- The marble holder was printed

### 09/05 
- Attached the marble holder to the base
- Testing basic movement: functionality of the left and right motor
- Josh and Toby modified code to enable some movement throughout maze
- Battery holder was connected to the top base 
- Testing the robot on the maze and debugging issues 
- Right motor is not functioning properly 
- Right motor problem has been fixed
- Testing code on robot and making adjustments to fix errors
- Re-testing the robot on the maze using modified code
- Errors were identified both in code and in hardware: Initially, we thought the robot had followed the white line but could not correct itself when the colour black was scanned by the camera. We concluded that our code needed to be altered (by decreasing the int defaultMicroSec and int defaultSpeed) in order for the robot to change direction in time. After multiple testing and debugging, we reached the final conclusion that in fact one of the motors is slower than the other and that there were errors in our code
- Re-testing the robot on the maze using modified code: The robot followed the white line but turned at a slow speed and went off track but could not correct itself
- Re-tested the robot on the maze using modified code: (EXTREME PROGRESS) The robot followed the white line at a slow speed and could turn at corners properly (without going off track) after camera angle was changed. 
- Re-tested the robot on the maze using modified code: The sample speed was changed but the robot was moving extremely slow on the maze. 
- Re-tested the robot on the maze using modified code: The sample speed, defaultSpeed and other speed were adjusted multiple times. The robot followed the white line properly at a slightly faster pace. More soldering needs to be done. 

### 10/05
- Attached the switch to the battery and base
- Applied modified code to robot
- Testing the robot on the maze: Speed is too slow therefore the robot isn't moving. The defaultSpeed and sample speed have been adjusted. 
- Re-testing the robot on the maze: Sample speed is too slow therefore the robot isn't reading the white line fast enough for the speed it is moving at. The sample speed has been adjusted. 
- Re-testing the robot on the maze: Turn speed is too fast but defaultSpeed is ok. The robot is turning too fast for the defaultSpeed therefore it is going off track. Adjustment must be made to turn speed. 
- Re-testing the robot on the maze: (EXTREME DRAWBACK) Adjustments have been made but the robot is no longer following the white line. defaultSpeed and sample speed has been adjusted back to the original values.
- Re-testing the robot on the maze: The robot can now follow the white line but not as precisely as before. Improvements need to be made in order for the robot to correct itself (reverse etc.) when the camera has scanned black. 
- Re-testing the robot on the maze: The robot can follow the white line properly but at certain bends in the maze, the robot cannot turn fast enough therefore the turn speed needs to be increased slightly. 
- Re-testing the robot on the maze: The robot follows the line at a moderate speed but at certain bends in the maze, the robot only sees black therefore it gets confused. Modification has been made in order for the robot to correct itself and reverse when black is detected by the camera.
- Re-testing the robot on the maze: The robot is reversing when required but is not reversing enough therefore the reverse time needs to be increased.
- Re-testing the robot on maze: The robot is reversing still but the reverse speed needs more power therefore the reverse speed needs to be adjusted and the defaultSpeed is increased. 
- Re-testing the robot on maze: The robot is moving through the maze but the turn is too wide therefore the turn speed needs to be adjusted back to our previous value.
- Re-tesing the robot on maze: The robot moved through the maze and turned correctly but the reverse time needs to be increased.
- Re-testing the robot on maze: The robot corrects it self well and breaks at max white but the turn is too wide therefore the turn speed and reverse speed needs to be adjusted. 
- Re-testing the robot on maze: (EXTREMELY GOOD RUN) The robot turns better and corrects itself properly but the turn is still quite wide therefore the defaultSpeed needs to be adjusted for the inside wheel speed.
- Re-testing the robot on maze: (PERFECT RUN) The robot is turning extremely well at a lower speed. Begin programming next part ----> 

### 14/05

- Testing the code to open the first gate
- Adjusting speeds in order for the robot to move and take bends in the maze smoothly
- The gate is opening and the robot is moving through it at an appropriate time. The robot then moves through the maze smoothly.

### 15/05

- Compiled different versions of code and tested it the robot on the maze
- Writing code for quadrant 3: beginning with the code that makes the robot turn at a right angle which includes establishing the values for each variable that is used
- Adjusting the time of the turn so it doesn't turn too fast or too slow
- Testing the robot on maze: The robot is continuously making a 360 degree turn therefore code needs to be looked at again and adjustments need to be made. 

### 16/05

- Cleaned up code so that it is systematic and easy to follow
- Writing code so that the robot stops at the orange line and also clearly makes left and right turns when required
- (EXTREMELY PROMISING) Test run to see if the robot correctly makes left and right turns when required. Adjustments need to be made to the pivotSpeed and defaultSpeed
- (EXTREMELY EXTREMELY PROMISING) The robot is turning fairly correctly when required now we need to put together the code with the master copy so that it runs the maze up to the end of Quadrant 3
- Minor setback after code was put together - robot isn't turning properly like the previous run therefore adjustments are being made to motor speed
- (HIGHLY PROMISING) The robot is moving correctly but the right and left turns are slightly off but the robot has reached the end
- (SUCCESSFUL RUN) The robot is moving correctly from the beginning of the maze to the end of Quadrant 3.

### 18/05

- Printing out the parts to connect the sensors to the robot
- Attaching the front sensor to the robot
- Writing code so that the robot stops at the orange line

### 22/05 

- The sensors are being attached to the robot 
- Testing the sensors

### 23/05

- Originally there were 3 sensors connected to the robot, all of which are long-range sensors. After testing them out, we reached the conclusion that the robot would need one long-range sensor in the front and two-range sensors on the sides in order to move through the maze. 
- The new sensors have been attached to the robot and code for the maze is being tested
- The robot is moving but continuously turns left and hits the wall 
- We are currently stuck in a deep dark hole. Every member is feeling all types of confused. The problem is hard to identify. 
- The plan is to add back sensors to the robot tomorrow and hope for the best

### 24/05

- The plan was to add back sensors to the robot but today we decided to code without them
- Code for Quadrant 4 is successful: minor tweaks have been made to speed so that the robot moves fast and efficiently through the maze
- The full code has been tested on the maze multiple times and we have had many SUCCESSFUL attempts
- The switch has been attached to the top of the robot 
- THRASHER GOT US 100% YAY!
