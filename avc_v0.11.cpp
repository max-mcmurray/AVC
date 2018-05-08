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

//written by Joshua Hindley
void detectLine()
{
	take_picture();
	for(int i = 0; i < 320; i++)
	{
		int pix = get_pixel(i, rowToScan, 3);
		if(pix > min)
			min = pix;
		if(pix < max)
			max = pix;
	}
	int threshold = (max + minimum) / 2;
	int weight = -160;
	int amountToTurn = 0;
	for(int i  = 0; i < 320; i++)
	{
		int pixelValue = get_pixel(rowToScan, i, 3);
		amountToTurn += (weight * pixelValue)
		weight++;
		if(weight == 0)
			weight = 1;
	}

}
void detectLineToby(x_pixels, y, white_boundary) //x_pixels: how many pixels to scan in one row - must produce a integer when 320/row_pixels
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
//written by Toby Stayner
// in progress - follows left side of the maze needs more information
void navigateWalledMaze()
{
	int distanceThreshold = 300; //may need to change this and create different thresholds for left and right- TEST THIS
	int adc_reading_left = read_analog(0);
	int adc_reading_front = read_analog(1);
	int adc_reading_right = read_analog(2);
	if(adc_reading_left > distanceThreshold){ // if there is a space to the left, turn left
		pivotLeft(); //need timings 
		goForward(); // go forward 1 section (grid e.g. 18cm by 18 cm)- TEST THIS
	}
	else if(adc_reading_front > distanceThreshold){ // do this if can't go left
		goForward(); 
	}
	else if(adc_reading_right > distance Threshold){ // do this if only valid space is to the right
		pivotRight();
		goForward();
	}
	else{ // do this when reaching a dead end
		pivotRight();
		pivotRight();
	}
}

//waits for the gate in the walled maze to open and goes through it when does
void waitForGateToOpen()
{
}
