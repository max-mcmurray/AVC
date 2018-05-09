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
