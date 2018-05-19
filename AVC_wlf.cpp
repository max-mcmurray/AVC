//This program is the intellectual property of TriTeam.
//This program was programmed by Joshua Hindley, Ben Robertson, Max McMurray, Penny Peneueta and Toby Stayner

#include <stdio.h>
#include <time.h>
#include <exception>
#include <utility>
#include "E101.h"

/////////////////////////////////////////////////////////////////////
///////////////////////////// VARIABLES /////////////////////////////
/////////////////////////////////////////////////////////////////////

int leftMotor = 1;
int rightMotor = 2;

//variables for the picture
int width = 319;
int height = 239;
int rowToScan = height/2;
int columnToScan = width/2;

//variables for the speed
int straightSpeed = -50;
int reverseSpeed = 50;
int insideWheelSpeed = -25;
int turningWheelSpeed = -60;

//variable for the time (sleep1)
int defaultSec = 0;
int defaultMicroSec  = 2000; 	// 2ms or 0.002 seconds 
int reverseMicroSec = 500000;	// 500ms or 0.5 seconds

//variables for the minimum and maximum color
int max;
int min;

//variables for determining when to reverse or change quadrant
int blackValue = 100;
int whiteValue = 150;

//variables for pivoting
int rightAngleMSec = 400000; 	// 400ms or 0.4 seconds
double pivotSpeed = -60;

//declaration of all the methods
void openStartGate();
void detectLine();
void lineMaze();
void goForward(int forwardMicroSec);
void reverse(int sec, int microsec);
void turnLeft(int sec, int microsec);
void turnRight(int sec, int microsec);
void pivotLeft(int sec, int microsec, double speed);
void pivotRight(int sec, int microsec, double speed);
double getAmountToTurn(double threshold);
std::pair<int, int> findMaxAndMin();

/////////////////////////////////////////////////////////////////////
////////////////////////////// METHODS //////////////////////////////
/////////////////////////////////////////////////////////////////////

//main method. determines which method to call
int main()
{
	init();
	//call the openStartGate method to complete quadrant 1
	openStartGate();
	sleep1(0, 200000);
	//call the detectLine method to complete quadrant 2
	detectLine();
	goForward(200000);
	//call the lineMaze method to complete quadrant 3
	lineMaze();
	return 0;
}

//opens the gate at the start of the course, completing the first quadrant
//written by Penny Peneueta
void openStartGate()
{
	//variables for connecting to the server
	char server_addr[15] = "130.195.6.196";
	int port = 1024;
	char message[24] = "Please";
	
	//connects to the server, sends a message, receives a message and sends the received message
	connect_to_server(server_addr, port);
	send_to_server(message);
	receive_from_server(message);
	send_to_server(message);
	//prints to the console
	printf("Gate opened.\n");
	printf("******************Quadrant 1 completed.\n\n");
}

//finds where the white line is and calls methods to move the AV stay on the line
//written by Joshua Hindley
void detectLine()
{
	try{
		while(true)
		{
			
			
			
			
			std::pair<int, int>(max, min) = findMaxAndMin();
			/* FIND OUT IF THIS WORKS */
			printf("Max: %d\n", max);
			printf("Min: %d\n", min);
			
			
			
			
			
			/*
			
			//set the max and min values
			max = 0;
			min = 255;
			take_picture();
			
			
			//POTENTIALLY WRITE A FUNCTION TO GET THE MAXIMUM
			//AND MINIMUM VALUES OF THE PIXEL COLORS
			
			
			for(int i = 0; i < 320; i++)
			{
				//gets a pixel from the centre row (rowToScan) of the picture
				int pix = get_pixel(rowToScan, i, 3);
				//stores the max and min pixel value
				if(pix < min)
					min = pix;
				if(pix > max)
					max = pix;
			}
			*/
			//if all the rowToScan pixels are black
			if(max < blackValue)
			{
				reverse(defaultSec, reverseMicroSec);
			}
			//if all the rowToScan pixels are white
			else if(min > blackValue)
			{
				//print to console
				printf("******************Quadrant 2 completed\n\n");
				return;
			}
			else
			{
				//calculates the threshold and calls the getAmountToTurn method to determine the amount to turn
				int threshold = (max + min) / 2;
				double amountToTurn = getAmountToTurn(threshold);
				if(amountToTurn <= 20 && amountToTurn >= -20) //CHANGE THIS VALUE TO CHANGE HOW OFTEN IT TURNS
				{
					goForward(defaultMicroSec);
				}
				/*
				CHANGE THIS POTENTIALLY SO THAT THE ROBOT TURNS A
				SMALLER AMOUNT IF THE ROBOT IS MORE CENTRED ON THE LINE
				*/
				else if(amountToTurn > 20) //turn to the right
				{		
					turnRight(defaultSec, defaultMicroSec);
				}
				else //turn to the left
				{	
					turnLeft(defaultSec, defaultMicroSec);
				}
			}
		}
	
	}
	//if an error occurs
	catch(const std::exception& e)
	{
		printf("An error occured!\n");
	}
	//set the motor's speeds to zero
	set_motor(leftMotor, 0);
	set_motor(rightMotor, 0);
}

//Follows lines in the form of a maze
//Written by Max 
void lineMaze() 
{
	bool justTurned = false;
    	try{
		while(true)
		{
			//set the max and min values
		   	max = 0;
		    	min = 255;
		    	take_picture();
		    	for(int i = 0; i < 320; i++)
		    	{
				//gets a pixel from the centre row (rowToScan) of the picture
				int pix = get_pixel(rowToScan, i, 3);
				//stores the max and min pixel value
				if(pix < min)
			   		min = pix;
				if(pix > max)
			    		max = pix;
		    	}
			//if all the pixels are black
		    	if(max < blackValue + 25)
		    	{
				if (!justTurned) 
				{
					//pivots to the left
			    		pivotLeft(0, rightAngleMSec, pivotSpeed);
			    		justTurned = true;
			    		sleep1(0, 500000);
				}
				else 
				{
					//pivots to the right twice
			   		pivotRight(0, rightAngleMSec, pivotSpeed);
			    		sleep1(0, 500000);
			    		pivotRight(0, rightAngleMSec, pivotSpeed);
			    		justTurned = false;
			    		sleep1(0, 500000);
				}
		    	}
		   	else
		    	{
				justTurned = false;
				//calculates the threshold and calls the getAmountToTurn method to determine the amount to turn
				int threshold = (max + min) / 2;
				double amountToTurn = getAmountToTurn(threshold);
				if(amountToTurn <= 20 && amountToTurn >= -20) 
				{
			    		goForward(defaultMicroSec);			   
				}
				else if(amountToTurn > 20) //turn to the right
				{
			    		turnRight(defaultSec, defaultMicroSec);			 
				}
				else //turn to the left
				{
			   		turnLeft(defaultSec, defaultMicroSec);
				}
		    	}
			//if the centre pixel of the image is orange
		    	if((get_pixel(160, 120, 0) > 150) & (get_pixel(160, 120, 2) < 100))
		    	{
				//print to the console
				printf("******************Quadrant 3 completed\n");
				//set the motor speeds to zero
				set_motor(leftMotor, 0);
				set_motor(rightMotor, 0);
				return;
		    	}
		}
	}
	//if an error occurs
    	catch(const std::exception& e)
	{
		printf("An error occured\n");
	}
	//set the motor speeds to zero
	set_motor(leftMotor, 0);
	set_motor(rightMotor, 0);
}

//moves the AV forward
//written by Ben Robertson
void goForward(int forwardMicroSec)
{
	set_motor(leftMotor, straightSpeed);
	set_motor(rightMotor, straightSpeed);
	
	sleep1(defaultSec, forwardMicroSec);
}

//revereses the robot
//written by Ben Robertson
void reverse(int sec, int microSec)
{
	set_motor(leftMotor, reverseSpeed);
	set_motor(rightMotor, reverseSpeed);
	
	sleep1(sec, microSec);
}

//turns the AV left by moving one wheel
//written by Ben Robertson
void turnLeft(int sec, int microsec)
{
	set_motor(leftMotor, insideWheelSpeed);
	set_motor(rightMotor, turningWheelSpeed);
	
	sleep1(sec, microsec);
}

//turns the AV right by moving one wheel
//written by Ben Robertson
void turnRight(int sec, int microsec)
{
	set_motor(leftMotor, turningWheelSpeed);
	set_motor(rightMotor, insideWheelSpeed);
	
	sleep1(sec, microsec);
}

//pivots the AV to the left at a point
//written by Ben Robertson
void pivotLeft(int sec, int microsec, double speed)
{
	set_motor(leftMotor, -(speed + 2));
	set_motor(rightMotor, (speed + 2));
	
	sleep1(sec, microsec);
	
	set_motor(leftMotor, 0);
	set_motor(rightMotor, 0);
}

//pivots the AV to the right at a point
//written by Ben Robertson
void pivotRight(int sec, int microsec, double speed)
{
	set_motor(leftMotor, speed - 2);
	set_motor(rightMotor, -(speed - 2));
	
	sleep1(sec, microsec);
	
	set_motor(leftMotor, 0);
	set_motor(rightMotor, 0);
}

std::pair<int, int> findMaxAndMin()
{
	//set the max and min values
	int maximum = 0;
	int minimum = 255;
	take_picture();
	for(int i = 0; i < 320; i++)
	{
		//gets a pixel from the centre row (rowToScan) of the picture
		int pix = get_pixel(rowToScan, i, 3);
		//stores the max and min pixel value
		if(pix < minimum)
			minimum = pix;
		if(pix > maximum)
			maximum = pix;
	}
	return std::pair<int, int>(maximum, minimum);
}

//calculates and returns the amount to turn
//written by Joshua Hindley
double getAmountToTurn(int threshold)
{
	int weight = -160;
	double amountToTurn = 0;
	for(int i  = 0; i < 320; i++)
	{
		//gets a pixel from the centre row (rowToScan) of the picture
		int pixelValue = get_pixel(rowToScan, i, 3);
		//if the pixel is darker than the threshold
		if(pixelValue < threshold)
			pixelValue = 0;
		//if the pixel is lighter than the threshold
		else
			pixelValue = 1;
		//increases (or decreases where weight is negative) the amount to turn
		amountToTurn += (weight * pixelValue);
		weight++;
		if(weight == 0)
			weight = 1;
	}
	//returns the amountToTurn
	return amountToTurn;
}
