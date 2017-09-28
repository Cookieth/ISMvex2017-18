#pragma config(Sensor, dgtl1,  ,               sensorTouch)
#pragma config(Sensor, dgtl9,  RightBottomEnc, sensorQuadEncoder)
#pragma config(Sensor, dgtl11, LeftBottomEnc,  sensorQuadEncoder)
#pragma config(Motor,  port1,           leftMotors,    tmotorVex393_HBridge, openLoop, driveLeft)
#pragma config(Motor,  port2,           rightMotors,   tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port3,           leftArm,       tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port4,           rightArm,      tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port5,           lifters,       tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port6,           clawMovers,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           claw,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

//Motor on values
int leftMotors = 127;
int rightMotors = 100;

//Central Functions Section
void controllerBasic();
void turnAround();

//Drive Controller Section
void Arcade(int Ch1, int Ch2);
void allOff();
void motorForward();
void motorBackward();
void motorLeftOn();
void motorRightOn();
void motorPointC();
void motorPointCC();
void driveDirectionDuration(int direction, int duration);

//==================================================================================================
//                     		      T A S K   S E C T I O N
//--------------------------------------------------------------------------------------------------
//			FUNCTIONS:
//				PRE_AUTON
//				AUTONOMOUS
//				USER CONTROL
//==================================================================================================

void pre_auton()
{
	//I DON'T THINK I'M DOING ANYTHING HERE
}

task autonomous()
{
	
	//1 = Forward
	//2 = Backward
	//3 = MOTOR Left
	//4 = MOTOR Right
	int forward = 1;
	int backward = 2;
	int left = 3;
	int right = 4;
	int pointC = 5;
	int pointCC = 6;
	
	//180D without weight is 1120
	//180D with weight is 
	
	driveDirectionDuration(forward, 2200);
	driveDirectionDuration(left, 1000);
	driveDirectionDuration(pointC, 1240);
	driveDirectionDuration(forward, 2200);
	
	
	allOff();
}

task usercontrol(){
	while (true){
		controllerBasic();
		turnAround();
		
		//if(sensorValue[RightBottomEnc]+sensorValue[RightBottomEnc] > 2){
			
		//}
		//else if(sensorValue[RightBottomEnc]+sensorValue[RightBottomEnc] > 2){
			
		// }
	}
}	

//==================================================================================================
//                           C E N T R A L   F U N C T I O N S   S E C T I O N
//--------------------------------------------------------------------------------------------------
//			MAIN FUNCTIONS:
//				1. CONTROLLER BASIC
//				2. TURN AROUND
//				3. LIFT BASIC
//
//			CONTROLLER INDEX:
//				1. DRIVE CONTROLLER SECTION
//				2. LIFT CONTROLLER SECTION
//==================================================================================================

void controllerBasic(){
	
	Arcade(vexRT(Ch1), vexRT(Ch2));
	
	if(vexRT[Btn5U] == 1){
		motor[leftLifter] = 127;
		motor[rightLifter] = 127;
		wait1Msec(0300);
		motor[leftLifter] = 0;
		motor[rightLifter] = 0;
	}
	else if(vexRT[Btn5D] == 1){
		motor[leftLifter] = -127;
		motor[rightLifter] = -127;
		wait1Msec(0300);
		motor[leftLifter] = 0;
		motor[rightLifter] = 0;
	}
	
	while(vexRT[Btn7U] == 1){
		motorForward();
		motorBackward();
		motorLeftOn();
		motorRightOn();
	}
}

void turnAround(){
	if(vexRT[Btn8D] == 1){
		motor[frontLeft] = 127;
		motor[backLeft] = 127;

		motor[frontRight] = -127;
		motor[backRight] = -127;

		wait1Msec(2125);

		allOff();
	}
}

//==================================================================================================
//                             D R I V E   C O N T R O L L E R   S E C T I O N
//==================================================================================================

void Arcade(int Ch1, int Ch2){
	if(Ch1<=-30){
		motor[backRight] = -Ch1;
		motor[backLeft] = Ch2;
		motor[frontRight] = -Ch1;
		motor[frontLeft] = Ch2;
	}
	else if(Ch1>=30){
		motor[backRight] = Ch2;
		motor[backLeft] = Ch1;
		motor[frontRight] = Ch2;
		motor[frontLeft] = Ch1;
	}
	else{
		motor[backRight] = Ch2;
		motor[backLeft] = Ch2;
		motor[frontRight] = Ch2;
		motor[frontLeft] = Ch2;
}
}

void allOff(){
	motor[backLeft] = 0;
	motor[backRight] = 0;
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
}

void motorForward(){
	motor[backLeft] = leftMotors;
	motor[backRight] = rightMotors;
	motor[frontLeft] = leftMotors;
	motor[frontRight] = rightMotors;
}

void motorBackward(){
	motor[backLeft] = -leftMotors;
	motor[backRight] = -rightMotors;
	motor[frontLeft] = -leftMotors;
	motor[frontRight] = -rightMotors;
}

void motorLeftOn(){
	motor[backLeft] = leftMotors;
	motor[backRight] = 0;
	motor[frontLeft] = leftMotors;
	motor[frontRight] = 0;
}

void motorRightOn(){
	motor[backLeft] = 0;
	motor[backRight] = rightMotors;
	motor[frontLeft] = 0;
	motor[frontRight] = rightMotors;
}

void motorPointCC(){
	motor[backLeft] = -leftMotors;
	motor[backRight] = rightMotors;
	motor[frontLeft] = -leftMotors;
	motor[frontRight] = rightMotors;
}

void motorPointC(){
	motor[backLeft] = leftMotors;
	motor[backRight] = -rightMotors;
	motor[frontLeft] = leftMotors;
	motor[frontRight] = -rightMotors;
}

void driveDirectionDuration(int direction, int duration){
	
	//1 = Forward
	//2 = Backward
	//3 = MOTOR Left
	//4 = MOTOR Right
	
	
	if(direction == 1){
		motorForward();
		wait1Msec(duration);
	}
	else if(direction == 2){
		motorBackward();
		wait1Msec(duration);
	}
	else if(direction == 3){
		motorLeftOn();
		wait1Msec(duration);
	}
	else if(direction == 4){
		motorRightOn();
		wait1Msec(duration);
	}
	else if(direction == 5){
		motorPointC();
		wait1Msec(duration);
	}
	else if(direction ==6){
		motorPointCC();
		wait1Msec(duration);
	}
	else{
	
	}
}
