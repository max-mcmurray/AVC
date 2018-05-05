//This program is the intellectual property of TriTeam.
//This program was programmed by Joshua Hindley, Ben Robertson, Max McMurray, Penny Peneueta and Toby Stayner

#include <stdio.h>
#include <time.h>
#include "E101.h"

int leftMotor = 1;
int rightMotor = 2;		// May be wrong way around
int rowToScan = 120;
int max = 0;
int min = 255;

//main method. determines which method to call
void main()
{
	init();
}

//opens the gate at the start of the course, completing the first quadrant
void openStartGate()
{
}

//finds where the white line is and calls methods to move the AV stay on the line
void detectLine()
{
	take_picture();
	for(int i = 0; i < 320; i++)
	{
		int pix = get_pixel(rowToScan, i, 3);
		if(pix > min)
			min = pix;
		if(pix < max)
			max = pix;
	}
}

//moves the AV forward
//written by Joshua Hindley
void goForward(int sec, int microsec, double speed)
{
	set_motor(leftMotor, speed);
	set_motor(rightMotor, speed);
	
	sleep1(sec, microsec);
	
	set_motor(leftMotor, 0);
	set_motor(rightMotor, 0);
}

//turns the AV left by moving one wheel
//written by Ben Robertson
void turnLeft(int sec, int microsec, double speed)
{
	set_motor(leftMotor, 0);
	set_motor(rightMotor, speed);
	
	sleep1(sec, microsec);

	set_motor(rightMotor, 0);
}

//turns the AV right by moving one wheel
//written by Joshua Hindley
void turnRight(int sec, int microsec, double speed)
{
	set_motor(leftMotor, speed);
	set_motor(rightMotor, 0);
	
	sleep1(sec, microsec);
	
	set_motor(leftMotor, 0);
}

//pivots the AV to the left at a point
//written by Joshua Hindley
void pivotLeft(int sec, int microsec, double speed)
{
	set_motor(leftMotor, -speed);
	set_motor(rightMotor, speed);
	
	sleep1(sec, microsec);
	
	set_motor(leftMotor, 0);
	set_motor(rightMotor, 0);
}

//pivots the AV to the right at a point
void pivotRight(int sec, int microsec, double speed)
{
}


//follows the line to solve the line maze detecting the line
//and using an algorithm to complete the third quadrant
void navigateLineMaze()
{
}

//follows the left/right wall of the maze, completing the final quadrant
void navigateWalledMaze()
{
}

//waits for the gate in the walled maze to open and goes through it when does
void waitForGateToOpen()
{
}
