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
}

// returns true when red is detected, false when not
// written by Toby Stayner
bool detectRed(int min, int max)
	// where min is the min red-ish value we want to detect and max is the highest
	// green and blue can be before detecting something else than red
{
	take_picture(); // takes an image
	for(int i = 0; i < 319; i++) // loops for 320 times (amount of x pixels)
	{
		int pix_red = get_pixel(i, rowToScan, 0); // get the red pixel value
		int pix_green = get_pixel(i, rowToScan, 1); // get the green pixel value
		int pix_blue = get_pixel(i, rowToScan, 2); // get the blue pixel value
		if(pix_red > min && pix_green < max && pix_blue < max) // detect red if red is high, green low and blue low
			return 1; // return true
		else{ // if not red
			return 0; // return false
		}
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
//written by Toby Stayner
// in progress - follows left side of the maze needs more information
bool sideWallDetect = 0;
int frontThreshold = 300; //may need to change this and create different thresholds for left and right- TEST THIS
int wallThreshold = 300; 
int noiseConstant = 50;
int leftSensor = ;
int frontSensor = ;
int rightSensor = ;

void navigateWalledMaze(int left_sensor, front_sensor, right_sensor)
{
	while(1){
		int adc_reading_left = read_analog(left_sensor);
		int adc_reading_front = read_analog(front_sensor);
		int adc_reading_right = read_analog(right_sensor);
		// if there are nearby walls on both sides and can go forward
		if(adc_reading_left > wallThreshold & adc_reading_right > wallThreshold & adc_reading_front < frontThreshold){
			printf("Walls on both sides detected. Attempting to go forward.\n");
			centreWallMaze(adc_reading_left, adc_reading_right);
		}
		// if there is a path on the left
		else if(adc_reading_left < wallThreshold & adc_reading_right > wallThreshold){ 
			printf("Turning left.\n");
			turnLeft(defaultSec, defaultMicroSec);
			sleep1(0, 100000);
			while(sideWallDetect()){ // move forward until there is a wall on both sides
				goForward(defaultMicroSec);
			}
			goForward(100000);
		}
		// if there is no path to the left, but can go forward
		else if(adc_reading_left > wallThreshold & adc_reading_front < frontThreshold){ 
			printf("Going forward.\n");
			while(sideWallDetect()){ // move forward until there is a wall on both sides
				goForward(defaultMicroSec);
			}
			goForward(100000);
		}
		// if there is a path on the right only
		else if(adc_reading_left > wallThreshold & adc_reading_right < wallThreshold & adc_reading_front > frontThreshold)
			printf("Turning right.\n");
			turnRight(defaultSec, defaultMicroSec);
			sleep1(0, 100000);
			while(sideWallDetect()){ // move forward until there is a wall on both sides
				goForward(defaultMicroSec);
			}
			goForward(100000);
		}
	 	// if there are nearby walls on both sides and cannot go forward
		else if(adc_reading_left > wallThreshold & adc_reading_right > wallThreshold & adc_reading_front > frontThreshold){
			printf("Dead end detected! Turning around.\n");
			turnRight(defaultSec, defaultMicroSec); // need to multiply by a number e.g. 1.3 to do a 180
		}
	}
 
}

void centreWallMaze(int adc_reading_left, int avc_reading_right)
{
	if(adc_reading_left + noiseConstant < adc_reading_right){ // when AV is close to the left wall
		printf("Too close to left wall!\n");
		reverse(defaultSec, reverseMicroSec);
		pivotRight(defaultSec, defaultMircoSec, insideWheelSpeed);
	}
	else if(adc_reading_left > adc_reading_right + noiseConstant){ // when AV is close to the right wall
		printf("Too close to right wall!\n");
		reverse(defaultSec, reverseMicroSec);
		pivotLeft(defaultSec, defaultMircoSec, insideWheelSpeed);
	}
	else{
		goForward(defaultMicroSec);
	}
}

bool sideWallDetect(){
	int adc_reading_left = read_analog(left_sensor);
	int adc_reading_right = read_analog(right_sensor);
	if(adc_reading_left > wallThreshold & adc_reading_right > wallThreshold){ // if there is a wall on both sides
		return 1;
	}
	else{
		return 0;
	}
}
