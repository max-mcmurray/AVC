//This program is the intellectual property of TriTeam.
//This program was programmed by Joshua Hindley, Ben Robertson, Max McMurray, Penny Peneueta and Toby Stayner

#include <stdio.h>
#include <time.h>
#include <exception>
#include "E101.h"

/////////////////////////////////////////////////////////////////////
///////////////////////////// CONSTANTS /////////////////////////////
/////////////////////////////////////////////////////////////////////

int leftMotor = 1;
int rightMotor = 2;

int width = 319;
int height = 239;
int rowToScan = height/2;
int columnToScan = width/2;

int straightSpeed = -50;
int reverseSpeed = 50;
int insideWheelSpeed = -25;
int turningWheelSpeed = -60;

int defaultSec = 0;
int defaultMicroSec  = 2000; 	// 2ms or 0.002 seconds 
int reverseMicroSec = 500000;	// 500ms or 0.5 seconds

int max;
int min;

int blackValue = 100;
int whiteValue = 150;

int rightAngleMSec = 400000;
double pivotSpeed = -60;

void openStartGate();
void detectLine();
void lineMaze();

void goForward(int forwardMicroSec);
void reverse(int sec, int microsec);
void turnLeft(int sec, int microsec);
void turnRight(int sec, int microsec);
void pivotLeft(int sec, int microsec, double speed);
void pivotRight(int sec, int microsec, double speed);

/////////////////////////////////////////////////////////////////////
////////////////////////////// METHODS //////////////////////////////
/////////////////////////////////////////////////////////////////////

//main method. determines which method to call
int main()
{
	init();
	openStartGate();
	sleep1(0, 200000);
	detectLine();
	goForward(200000);
	lineMaze();
	return 0;
}

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
	printf("******************Quadrant 1 completed.\n\n");
}

//finds where the white line is and calls methods to move the AV stay on the line
//written by Joshua Hindley

void detectLine()
{
	try{
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
			else if(min > blackValue)
			{
				printf("******************Quadrant 2 completed\n\n");
				return;
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
		}
	
	}
	catch(const std::exception& e)
	{
		printf("An error occured\n");
	}
	set_motor(leftMotor, 0);
	set_motor(rightMotor, 0);
}

//Follows lines in the form of a maze
//Written by Max 

void lineMaze() {

	bool justTurned = false;
    try{
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
            
     
            if(max < blackValue+25)
            {
                if (!justTurned) {
                    pivotLeft(0, rightAngleMSec, pivotSpeed);
                    justTurned = true;
                    sleep1(0, 500000);
                }
                else {
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
                if(amountToTurn <= 20 && amountToTurn >= -20) 
                {
                    goForward(defaultMicroSec);
                    //sleep1(defaultSec, 100000);
					//set_motor(leftMotor, 0);
					//set_motor(rightMotor, 0);
                }
                else if(amountToTurn > 20) //turn to the right
                {
                    turnRight(defaultSec, defaultMicroSec);
                    //sleep1(defaultSec, 100000);
					//set_motor(leftMotor, 0);
					//set_motor(rightMotor, 0);
                }
                else //turn to the left
                {
                    turnLeft(defaultSec, defaultMicroSec);
                    //sleep1(defaultSec, 100000);
					//set_motor(leftMotor, 0);
					//set_motor(rightMotor, 0);
                }
            }
            
            if((get_pixel(160, 120, 0) > 150) & (get_pixel(160, 120, 2) < 100))
            {
                printf("******************Quadrant 3 completed\n");
                set_motor(leftMotor, 0);
                set_motor(rightMotor, 0);
                return;
            }
        }

    }
    catch(const std::exception& e) {
		printf("An error occured\n");
	}
	set_motor(leftMotor, 0);
	set_motor(rightMotor, 0);
}

//moves the AV forward
//written by Joshua Hindley

void goForward(int forwardMicroSec)
{
	//printf("Going forward.\n");
	set_motor(leftMotor, straightSpeed);
	set_motor(rightMotor, straightSpeed);
	
	sleep1(defaultSec, forwardMicroSec);
	
	//set_motor(leftMotor, 0);
	//set_motor(rightMotor, 0);
}

//revereses the robot
//written by Joshua Hindley

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

//pivots the AV to the left at a point
//written by Joshua Hindley

void pivotLeft(int sec, int microsec, double speed)
{
	set_motor(leftMotor, -(speed + 2));
	set_motor(rightMotor, (speed + 2));
	
	sleep1(sec, microsec);
	
	set_motor(leftMotor, 0);
	set_motor(rightMotor, 0);
}

//pivots the AV to the right at a point
//written by Joshua Hindley

void pivotRight(int sec, int microsec, double speed)
{
	set_motor(leftMotor, speed - 2);
	set_motor(rightMotor, -(speed - 2));
	
	sleep1(sec, microsec);
	
	set_motor(leftMotor, 0);
	set_motor(rightMotor, 0);
}
