//This program is the intellectual property of TriTeam.
//This program was programmed by Joshua Hindley, Ben Robertson, Max McMurray, Penny Peneueta and Toby Stayner

#include <stdio.h>
#include <time.h>
#include <exception>
#include "E101.h"

int leftMotor = 1;
int rightMotor = 2;		// May be wrong way around
int defaultSpeed = -25;
int reverseSpeed = 50;
int defaultSec = 0;
int defaultMicroSec  = 5000; 	//5ms or 0.1 seconds 
int reverseMicroSec = 500000;
int rowToScan = 119;
int columnToScan = SENDHELP;//whoops
int max = 0;
int min = 255;
int timesToRun = 4500;
int blackValue = 100;

void turnLeft(int sec, int microsec, double speed);
void turnRight(int sec, int microsec, double speed);
void goForward();
void reverse(int sec, int microsec);

//opens the gate at the start of the course, completing the first quadrant
void openStartGate()
{
}

//finds where the white line is and calls methods to move the AV stay on the line
//written by Joshua Hindley
void detectLine()
{
	//try{
	int times = 0;
	while(times < timesToRun)
	{
		max = 0;
		min = 255;
		int speed = defaultSpeed;
		take_picture();
		for(int i = 0; i < 320; i++)
		{
			int pix = get_pixel(rowToScan, i, 3);
			if(pix < min)
				min = pix;
			if(pix > max)
				max = pix;
		}
		if(max < blackValue)
		{
			reverse(defaultSec, reverseMicroSec);
		}
		else if(min > blackValue)
		{
			printf("*****BROKEN!*****\n");
			break;
		}
		else
		{
			int threshold = (max + min) / 2;
			int weight = -160;
			double amountToTurn = 0;
			for(int i  = 0; i < 320; i++)
			{
				int pixelValue = get_pixel(rowToScan, i, 3);
				if(pixelValue < threshold)
					pixelValue = 0;
				else
					pixelValue = 1;
				amountToTurn += (weight * pixelValue);
			weight++;
			if(weight == 0)
				weight = 1;
		}
		if(amountToTurn <= 7 && amountToTurn >= -7)
		{
			goForward();
			printf("GOING FORWARDSSS\n");
		}
		else if(amountToTurn > 7) //turn to the right
		{	//left motor needs to speed up
			//amountToTurn *= 0.1;
			//if(amountToTurn > 128)
				//amountToTurn = 128;
			speed -= 25;//amountToTurn; //can decrease by up to 128
			turnRight(defaultSec, defaultMicroSec, speed);
		}
		else //turn to the left
		{	//right motor needs to speed up
			//amountToTurn = -amountToTurn;
			//amountToTurn *= 0.1;
			//if(amountToTurn > 128)
				//amountToTurn = 128;
			speed -= 25;//amountToTurn; //can decrease up to 128
			turnLeft(defaultSec, defaultMicroSec, speed);
		}
		times++;
		}
		
	}
	set_motor(leftMotor, 0);
	set_motor(rightMotor, 0);
//}
//catch(exception e)
//{
	//set_motor(leftMotor, 0);
	//set_motor(rightMotor, 0);
//}
}

//For the third quadrent written by Max <3
void lineMaze() {
	int times = 0;
	while (times < timesToRun){
		
		takePicture();
		for (int pixel = 0; pixel < 320; pixel++){
			int pixelValue = get_pixel(rowToScan, pixel, 3);
			if (pixelValue < min) {
				min = pixelValue;
			}
			if (pixelValue > max) {
				max = pixelValue;
			}
		}
	}
}

//moves the AV forward
//written by Joshua Hindley
void goForward()
{
	set_motor(leftMotor, defaultSpeed);
	set_motor(rightMotor, defaultSpeed);
	
	sleep1(defaultSec, defaultMicroSec);
	
	//set_motor(leftMotor, 0);
	//set_motor(rightMotor, 0);
}

//turns the AV left by moving one wheel
//written by Ben Robertson
void turnLeft(int sec, int microsec, double speed)
{
	set_motor(leftMotor, defaultSpeed);
	set_motor(rightMotor, speed);
	
	sleep1(sec, microsec);

	//set_motor(rightMotor, 0);
	//set_motor(leftMotor, 0);
}

//turns the AV right by moving one wheel
//written by Joshua Hindley
void turnRight(int sec, int microsec, double speed)
{
	set_motor(leftMotor, speed);
	set_motor(rightMotor, defaultSpeed);
	
	sleep1(sec, microsec);
	
	//set_motor(leftMotor, 0);
	//set_motor(rightMotor, 0);
}

void reverse(int sec, int microSec)
{
	set_motor(leftMotor, reverseSpeed);
	set_motor(rightMotor, reverseSpeed);
	
	sleep1(sec, microSec);
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
//written by Joshua Hindley
void pivotRight(int sec, int microsec, double speed)
{
	set_motor(leftMotor, speed);
	set_motor(rightMotor, -speed);
	
	sleep1(sec, microsec);
	
	set_motor(leftMotor, 0);
	set_motor(rightMotor, 0);
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

//main method. determines which method to call
int main()
{
	init();
	detectLine();
	return 0;
}
