//This program is the intellectual property of TriTeam.
//This program was programmed by Joshua Hindley, Ben Robertson, Max McMurray, Penny Peneueta and Toby Stayner

#include <stdio.h>
#include <time.h>
#include <exception>
#include "E101.h"

/////////////////////////////////////////////////////////////////////
///////////////////////////// VARIABLES /////////////////////////////
/////////////////////////////////////////////////////////////////////

//motor port numbers
int leftMotor = 1;
int rightMotor = 2;

//picture variables
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
int maxMin[2];

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
double getAmountToTurn(int threshold);
void findMaxAndMin();
void stop();
void navigateWalledMaze();
void centreWallMaze();


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
	//openStartGate();
	goForward(200000);
	//call the lineMaze method to complete quadrant 3
	lineMaze();
	//openStartGate();
	navigateWalledMaze();
	stop();
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
			findMaxAndMin();
			//if all the rowToScan pixels are black
			if(maxMin[0] < blackValue)
			{
				reverse(defaultSec, reverseMicroSec);
			}
			//if all the rowToScan pixels are white
			else if(maxMin[1] > blackValue)
			{
				//print to console
				printf("******************Quadrant 2 completed\n\n");
				return;
			}
			else
			{
				//calculates the threshold and calls the getAmountToTurn method to determine the amount to turn
				int threshold = (maxMin[0] + maxMin[1]) / 2;
				double amountToTurn = getAmountToTurn(threshold);
				if(amountToTurn <= 1000 && amountToTurn >= -1000) //CHANGE THIS VALUE TO CHANGE HOW OFTEN IT TURNS
				{
					goForward(defaultMicroSec);
				}
				else if(amountToTurn > 1000) //turn to the right
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
	catch(const std::exception& e){
		printf("An error occured!\n");
	}
	//set the motor's speeds to zero
	stop();
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
		   	findMaxAndMin();
			//if all the pixels are black
		    if(maxMin[0] < blackValue + 25)
		    {
				if (!justTurned) 
				{
					//pivots to the left
			    	pivotLeft(0, rightAngleMSec / 2, pivotSpeed);
			    	justTurned = true;
			    	sleep1(0, 500000);
				}
				else 
				{
					//pivots to the right twice
			   		pivotRight(0, rightAngleMSec / 2, pivotSpeed);
			    	sleep1(0, 500000);
			    	pivotRight(0, rightAngleMSec / 2, pivotSpeed);
			    	justTurned = false;
			    	sleep1(0, 500000);
				}
		    }
		   	else
		    {
				justTurned = false;
				//calculates the threshold and calls the getAmountToTurn method to determine the amount to turn
				int threshold = (maxMin[0] + maxMin[1]) / 2;
				double amountToTurn = getAmountToTurn(threshold);
				if((amountToTurn <= 20) & (amountToTurn >= -20)) 
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
		    if( (get_pixel(160, 120, 0) > 150) & (get_pixel(160,120,1) < 80) & (get_pixel(160, 120, 2) < 70))
		    {
				//print to the console
				printf("******************Quadrant 3 completed\n");
				//set the motor speeds to zero
				stop();
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
	stop();
}

//follows the left wall of the maze, completing the final quadrant
//written by Toby Stayner

int frontThreshold = 350; // AV considers the robot has a wall in front anything larger than this
int wallThreshold = 450; // AV considers the robot has a wall either side anything larger than this
int noiseConstant; // amount of leeway before the left sensor is no longer considered equal to the right sensor
int forwardAfterTurn = 250000; // amount of time (microsecs) the AV should continue travelling forward once it has made a turn

int left_sensor = 2; // the number ports that the wires are physically connected to
int front_sensor = 1;
int right_sensor = 0;
int adc_reading_left;
int adc_reading_front;
int adc_reading_right;
bool seenRed = false;

void navigateWalledMaze()
{
	printf("Beggining***\n");
	goForward(500000);
	try{
		while(1)
		{
			adc_reading_left = read_analog(left_sensor); // read the sensor values and store them
			adc_reading_front = read_analog(front_sensor);
			adc_reading_right = read_analog(right_sensor);

			take_picture();
			//if the centre pixel of the image is red
		    if((get_pixel(160, 120, 0) > 200) & (get_pixel(160,120,1) < 100) & (get_pixel(160, 120, 2) < 150) & !seenRed)
		    {
				seenRed = true;
				goForward(900000);
				stop();
				adc_reading_front = read_analog(front_sensor);
				//if gate is open
				if((adc_reading_front < 75))
				{
					//while gate is open
					while(adc_reading_front < 75)
					{
						//wait for gate to close
						adc_reading_front = read_analog(front_sensor);
					}
				}
				//while gate is closed
				while(adc_reading_front > 75)
					{
						//wait for gate to open
						adc_reading_front = read_analog(front_sensor);
					}
		    }
			// if there are nearby walls on both sides and can go forward
			if((adc_reading_front < frontThreshold))
			{
				printf("Forward.\n");
				centreWallMaze();
			}

			// if there is a path on the left only
			else if((adc_reading_left > wallThreshold) & (adc_reading_front > frontThreshold))
			{ 
				printf("******************************Turning left.\nLeft: %d\nRight: %d\n", adc_reading_left, adc_reading_right);
				pivotLeft(0, rightAngleMSec, pivotSpeed);
				sleep1(0, 100000);
				goForward(forwardAfterTurn);
			}
			// if there are nearby walls on both sides and cannot go forward
			else if((adc_reading_left < wallThreshold) & (adc_reading_right < wallThreshold) & (adc_reading_front > frontThreshold))
			{
				printf("Dead end detected! Turning around.\n");
				pivotRight(0, rightAngleMSec, pivotSpeed);
				sleep1(0, 100000);
				pivotRight(0, rightAngleMSec, pivotSpeed);
				sleep1(0, 100000);
			}
			else
			{
				reverse(0, 200000);
			}
		}
	}
	catch(const std::exception& e)
	{
		printf("An error occured\n");
	}
	//set the motor speeds to zero
	stop();
 
}

void centreWallMaze()
{
	try
	{
		if((adc_reading_right < wallThreshold))
		{
			printf("********Turning Left\n");
			turnLeft(defaultSec, defaultMicroSec*40);
		}
		else if((adc_reading_right > wallThreshold))
		{
			printf("********Turning Right\n");
			turnRight(defaultSec, defaultMicroSec*40);
		}
		goForward(defaultMicroSec);
		sleep1(0, 10000);
	}
	catch(const std::exception& e)
	{
		printf("An error occured\n");
	}
	//set the motor speeds to zero
	stop();
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
	
	stop();
}

//pivots the AV to the right at a point
//written by Ben Robertson
void pivotRight(int sec, int microsec, double speed)
{
	set_motor(leftMotor, speed - 2);
	set_motor(rightMotor, -(speed - 2));
	
	sleep1(sec, microsec);
	
	stop();
}

//finds and returns the maximum and minimum color
//written by Joshua Hindley
void findMaxAndMin()
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
	maxMin[0] = maximum;
	maxMin[1] = minimum;
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

void stop() {
	set_motor(leftMotor, 0);
	set_motor(rightMotor, 0);
}
