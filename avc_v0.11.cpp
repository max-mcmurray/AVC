//This program is the intellectual property of TriTeam.
//This program was programmed by Joshua Hindley, Ben Robertson, Max McMurray, Penny Peneueta and Toby Stayner

#include <stdio.h>
#include <time.h>
#include "E101.h"

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
void detectLine(x_pixels, y, white_boundary) //x_pixels: how many pixels to scan in one row - must produce a integer when 320/row_pixels
{
	take_picture();
	for(int i = 0; i < x_pixels; i++)
	{
		int x = i*320/x_pixels;
		//unsigned char red = get_pixel(x, y, 0);
		//unsigned char green = get_pixel(x, y, 1);
		//unsigned char blue = get_pixel(x, y, 2);
		unsigned char white = get_pixel(x, y, 3);
		if(white > white_boundary)
		{
			//array	
		}
		
	}
	int total = 0
	for(int num i++)
	{
		total += num
	}
	white_average = total/i
}

//moves the AV forward
//written by Joshua Hindley
void goForward(int sec, int microsec, double speed)
{
	set_motor(1, speed);
	set_motor(2, speed);
	sleep1(sec, microsec);
	set_motor(1, 0);
	set_motor(2, 0);
}

//turns the AV left while moving forward
void turnLeft(int sec, int microsec, double speed)
{
}

//turns the AV right while moving forward
void turnRight(int sec, int microsec, double speed)
{
}

//pivots the AV to the left at a point
void pivotLeft(int sec, int microsec, double speed)
{
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
