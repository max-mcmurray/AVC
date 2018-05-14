//This program is the intellectual property of TriTeam.
//This program was programmed by Joshua Hindley, Ben Robertson, Max McMurray, Penny Peneueta and Toby Stayner

#include <stdio.h>
#include <time.h>
#include <exception>
#include "E101.h"

int leftMotor = 1;
int rightMotor = 2;		// May be wrong way around
int straightSpeed = -50;	//CHANGE THIS TO MAKE GOING STRAIGHT WORK PROPERLY
int insideWheelSpeed = -25;
int turningWheelSpeed = -60;
int reverseSpeed = 50;
int defaultSec = 0;
int defaultMicroSec  = 5000; 	//5ms or 0.005 seconds 
int reverseMicroSec = 500000;
int rowToScan = 119;//height/2;
//int columnToScan = width/2;	//whoops
int max = 0;
int min = 255;
//int timesToRun = 4500;
int blackValue = 100;
int whiteValue = 100;

//***************************************************************************************
//int width = mmmmmmmmowommmmmm;
//int height = HUFHUEFHIEHFIHFIOEF;
//int rightAngleMSec = mmmmmmmmmmmmmmmmmmmmmmmmmmm;
//double pivotSpeed = stufIGuess;
//***************************************************************************************

void detectLine();
void turnLeft(int sec, int microsec);
void turnRight(int sec, int microsec);
void goForward();
void reverse(int sec, int microsec);
void pivotLeft(int sec, int microsec, double speed);
void pivotRight(int sec, int microsec, double speed);

//opens the gate at the start of the course, completing the first quadrant
void openStartGate()
{
	char server_addr[15] = "130.195.6.196";
	int port = 1024;
	char message[24] = "Please";
	
	connect_to_server(server_addr, port);
	printf("Connecting to server.\n");
	send_to_server(message);
	//printf("Sending message: %s\n", message);
	receive_from_server(message);
	//printf("Received password: %s\n", message);
	send_to_server(message);
	printf("Sending password.\n");
	printf("Gate opened.\n");
	printf("Quadrant 1 completed.\n\n");
	sleep1(0, 200000);
	detectLine();
}

//finds where the white line is and calls methods to move the AV stay on the line
//written by Joshua Hindley
void detectLine()
{
	//try{
	while(true)
	{
		max = 0;
		min = 255;
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
		else if(min > whiteValue)
		{
			printf("*****BROKEN!*****\n");
			printf("Quadrant 2 completed");
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
			if(amountToTurn <= 20 && amountToTurn >= -20) //CHANGE THIS VALUE TO CHANGE HOW OFTEN IT TURNS
			{
				goForward();
			}	
			else if(amountToTurn > 20) //turn to the right
			{		
				turnRight(defaultSec, defaultMicroSec);
			}
			else //turn to the left
			{	
				turnLeft(defaultSec, defaultMicroSec);
			}
		//times++;
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

//For the third quadrant written by Max <3
void lineMaze() {
	int times = 0;
	//0 = top line. Proceeding numbers go clockwise
	int maxs[4] = {0, 0, 0, 0};
	int mins[4] = {255, 255, 255, 255};
	//while (times < timesToRun){
		
		//takePicture();
		
		//For line 0
		//for (int pixel = 0; pixel < height/2; pixel++) {
		//	int pixelValue = get_pixel(pixel, columnToScan, 3);
			//if (pixelValue < mins[0]) {
			//	mins[0] = pixelValue;
			//}
			//if (pixelValue > maxs[0]) {
			//	maxs[0] = pixelValue;
			//}
		//}
		
		//For line 1
		for (int pixel = 160; pixel < 320; pixel++) {
			int pixelValue = get_pixel(rowToScan, pixel, 3);
			if (pixelValue < mins[1]) {
				mins[1] = pixelValue;
			}
			if (pixelValue > maxs[1]) {
				maxs[1] = pixelValue;
			}
		}
		
		//For line 2
		//for (int pixel = height/2; pixel < height; pixel++) {
			//int pixelValue = get_pixel(pixel, columnToScan, 3);
			//if (pixelValue < mins[2]) {
			//	mins[2] = pixelValue;
			//}
			//if (pixelValue > maxs[2]) {
			//	maxs[2] = pixelValue;
			//}
		//}
		
		//For line 3
		for (int pixel = 0; pixel < 160; pixel++) {
			int pixelValue = get_pixel(rowToScan, pixel, 3);
			if (pixelValue < mins[3]) {
				mins[3] = pixelValue;
			}
			if (pixelValue > maxs[3]) {
				maxs[3] = pixelValue;
			}
		}

		//If given the opportunity to turn left then do so
		if (maxs[3] > whiteValue) {
            //pivotLeft(0, rightAngleMSec, pivotSpeed);
            goForward();
		}
		
		//If can't turn left but can go forward then go forward
		else if (maxs[0] > whiteValue) {
		    goForward();
		}
		
		//Turn right if can
		else if (maxs[1] > whiteValue) {
			//pivotRight(0, rightAngleMSec, pivotSpeed)
		}
		
		//Must be at dead end so turn round
		else {
			//pivotRight(0, rightAngleMSec*2, pivotSpeed)
		}

		//adjustToLine();//Mayyyyyyybe write this or make it work
		times++;
	//}
}


//moves the AV forward
//written by Joshua Hindley
void goForward()
{
	set_motor(leftMotor, straightSpeed);
	set_motor(rightMotor, straightSpeed);
	
	sleep1(defaultSec, defaultMicroSec);
	
	//set_motor(leftMotor, 0);
	//set_motor(rightMotor, 0);
}

//turns the AV left by moving one wheel
//written by Ben Robertson
void turnLeft(int sec, int microsec)
{
	set_motor(leftMotor, insideWheelSpeed);
	set_motor(rightMotor, turningWheelSpeed);
	
	sleep1(sec, microsec);

	//set_motor(rightMotor, 0);
	//set_motor(leftMotor, 0);
}

//turns the AV right by moving one wheel
//written by Joshua Hindley
void turnRight(int sec, int microsec)
{
	set_motor(leftMotor, turningWheelSpeed);
	set_motor(rightMotor, insideWheelSpeed);
	
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
	set_motor(leftMotor, -insideWheelSpeed);
	set_motor(rightMotor, insideWheelSpeed);
	
	sleep1(sec, microsec);
	
	set_motor(leftMotor, 0);
	set_motor(rightMotor, 0);
}

//pivots the AV to the right at a point
//written by Joshua Hindley
void pivotRight(int sec, int microsec, double speed)
{
	set_motor(leftMotor, insideWheelSpeed);
	set_motor(rightMotor, -insideWheelSpeed);
	
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
	openStartGate();
	return 0;
}
