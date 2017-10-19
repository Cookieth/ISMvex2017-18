#pragma config(Sensor, dgtl9,  RightBottomEnc, sensorQuadEncoder)
#pragma config(Sensor, dgtl11, LeftBottomEnc,  sensorQuadEncoder)
#pragma config(Motor,  port2,           leftMotors,    tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port3,           rightMotors,   tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port4,           leftArm,       tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port5,           rightArm,      tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port6,           lifters,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           clawMovers,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           claw,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

//Motor on values
int leftMotorsVal = 127;
int rightMotorsVal = 100;\


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
void driveFunct(int direction, int duration);

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
	int liftersUP = 7;
	int liftersDOWN = 8;
	int armsUP = 9;
	int armsDOWN = 10;

	//180D without weight is 1120
	//180D with weight is

	//**TO DO: INSERT AUTONOMOUS CODE**


	//ONE CONE ON HIGH STACK
	motor[leftArm] = 127;
	motor[rightArm] = 127;
	wait1Msec(850);
	motor[clawMovers] = 127;
	wait1Msec(750);
	motor[leftArm] = 0;
	motor[rightArm] = 0;
	wait1Msec(1000);
	motor[leftMotors] = 127;
	motor[rightMotors] = 20;
	wait1Msec(0370);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	motor[clawMovers] = -60;
	wait1Msec(0500);
	motor[clawMovers] = 0;
	motor[claw] = 127;
	wait1Msec(1000);
	motor[clawMovers] = 127;
	motor[claw] = 0;
	wait1Msec(1000);
	motor[leftMotors] = -127;
	motor[rightMotors] = -127;
	motor[leftArm] = -127;
	motor[rightArm] = -127;
	wait1Msec(400);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	wait1Msec(0100);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	wait1Msec(0300);

	//SKILLS:
	if(1==1){

	motor[rightMotors] = 127;
	wait1Msec(0100);
	motor[rightMotors] = 100;
	motor[leftMotors] = 127;
	wait1Msec(1500);
	motor[lifters] = 127;
	motor[rightMotors] = 0;
	motor[leftMotors] = 0;
	wait1Msec(1200);
	motor[lifters] = 0;
	motor[rightMotors] = 127;
	motor[leftMotors] = -127;
	wait1Msec(1100);
	motor[rightMotors] = 100;
	motor[leftMotors] = 127;
	wait1Msec(1600);

	motor[lifters] = -127;
	motor[rightMotors] = 0;
	motor[leftMotors] = 0;
	wait1Msec(1200);
	motor[lifters] = 0;
	motor[rightMotors] = -127;
	motor[leftMotors] = -127;
	wait1Msec(0500);
	motor[lifters] = 127;
	motor[rightMotors] = 0;
	motor[leftMotors] = 0;
	wait1Msec(1000);
	motor[lifters] = 0;
	motor[leftMotors] = -127;
	motor[rightMotors] = -127;
	wait1Msec(1000);

}

	//COMP:
	if(0==1){
	motor[clawMovers] = -127;
	motor[rightMotors] = 127;
	wait1Msec(0600);
	motor[rightMotors] = 0;
	wait1Msec(0600);
	motor[clawMovers] = 0;
	motor[claw] = 127;
	wait1Msec(1000);

	//move forward to grab the cone
	motor[leftMotors] = 127;
	motor[rightMotors] = 90;
	wait1Msec(0590);
	motor[rightMotors] = 0;
	motor[leftMotors] = 0;
	motor[claw] = -127;
	wait1Msec(1000);
	motor[clawMovers] = 127;
	wait1Msec(0800);


	//MOVING AWAY WITH CONE
	motor[leftMotors] = 0;
	motor[rightMotors] = 127;
	motor[lifters] = -127;
	wait1Msec(0600);
	motor[leftMotors] = 127;
	motor[rightMotors] = 0;
	motor[lifters] = 0;
	wait1Msec(0700);
	motor[leftMotors] = 100;
	motor[rightMotors] = 100;
	wait1Msec(1000);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	motor[lifters] = 127;
	wait1Msec(1000);
	}


	allMotorsOff();

	allOff();
}

task usercontrol(){
	while (true){
		controllerBasic();
		turnAround();
		
		
		//==========================AUTON TEST
		
		if(vexRT(Btn7UXmtr2) == 1){
		//ONE CONE ON HIGH STACK
	motor[leftArm] = 127;
	motor[rightArm] = 127;
	wait1Msec(850);
	motor[clawMovers] = 127;
	wait1Msec(750);
	motor[leftArm] = 0;
	motor[rightArm] = 0;
	wait1Msec(1000);
	motor[leftMotors] = 127;
	motor[rightMotors] = 20;
	wait1Msec(0370);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	motor[clawMovers] = -60;
	wait1Msec(0500);
	motor[clawMovers] = 0;
	motor[claw] = 127;
	wait1Msec(1000);
	motor[clawMovers] = 127;
	motor[claw] = 0;
	wait1Msec(1000);
	motor[clawMovers] = 0;
	wait1Msec(0500);
	motor[leftMotors] = -127;
	motor[rightMotors] = -127;
	motor[leftArm] = -127;
	motor[rightArm] = -127;
	wait1Msec(400);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	wait1Msec(0100);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	wait1Msec(0300);

	//SKILLS:
	if(1==1){

	motor[rightMotors] = 127;
	wait1Msec(0100);
	motor[rightMotors] = 100;
	motor[leftMotors] = 127;
	wait1Msec(1250);
	motor[lifters] = 127;
	motor[rightMotors] = 0;
	motor[leftMotors] = 0;
	wait1Msec(1200);
	motor[lifters] = 0;
	motor[rightMotors] = 127;
	motor[leftMotors] = -127;
	wait1Msec(1200);
	motor[rightMotors] = 100;
	motor[leftMotors] = 127;
	wait1Msec(2000);

	motor[lifters] = -127;
	motor[rightMotors] = 0;
	motor[leftMotors] = 0;
	wait1Msec(1200);
	motor[lifters] = 0;
	motor[rightMotors] = -127;
	motor[leftMotors] = -127;
	wait1Msec(0500);
	motor[lifters] = 127;
	wait1Msec(1000);
	motor[lifters] = 0;
	motor[leftMotors] = -127;
	motor[rightMotors] = -127;
	wait1Msec(1000);

}	
	}
	
		
		
		//===========================AUTON TEST
		
		
		
		
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

	//Arcade(vexRT(Ch4), vexRT(Ch3));

	//========
	//BASE
	if(vexRT[Btn8D] == 1) {
		motor[claw] = 127; //open claw
		wait1Msec(200);
		motor[claw] = 0;
		motorForward(); //move forward
		wait1Msec(390);
		allOff();
		motor[claw] = -127; //close claw
		wait1Msec(250);
		motor[claw] = 0;
		motorBackward(); //move backward
		wait1Msec(390);
		allOff();

	}
	else if(vexRT[Btn8U] == 1) {
		motorBackward();
		wait1Msec(190);
	}
	else if(vexRT[Btn8R] == 1) {
		motorBackward();
		wait1Msec(380);
	}
	else if(vexRT[Btn7U] == 1) {
		motorForward();
	}
	else if(vexRT[Btn7D] == 1) {
		motorBackward();
	}
	else if(vexRT[Btn7L] == 1) {
		motorPointCC();
	}
	else if(vexRT[Btn7R] == 1) {
		motorPointC();
	}
	else {
		motor[leftMotors] = vexRT(Ch3);
		motor[rightMotors] = vexRT(Ch2);
	}

	//========
	//LIFTERS
	if(vexRT[Btn5U] == 1 || vexRT[Btn5UXmtr2] == 1){
		motor[lifters] = 127;
	}
	else if(vexRT[Btn5D] == 1 || vexRT[Btn5D] == 1){
		motor[lifters] = -127;
	}
	else{
		motor[lifters] = 0;
	}

	//========
	//ARMS
	motor[leftArm] = vexRT(Ch3Xmtr2);
	motor[rightArm] = vexRT(Ch3Xmtr2);

	//========
	//SERVOS
	//Zach'll put rubber bands to stop claw from walling when holding the claw
	//if claw still falls, Zach will change the gearing and remodify

	motor(clawMovers) = vexRT(Ch2Xmtr2);

	if(vexRT[Btn6UXmtr2] == 1 || vexRT[Btn6U] == 1){
		motor[claw] = 127; //this closes claw, not changed
	}
	else if(vexRT[Btn6DXmtr2] == 1 || vexRT[Btn6D] == 1){
		motor[claw] = -127; //this opens claw, changed from positive to negative
	}
	else{
		motor[claw] = 0; //removed other stop motor statements
	}



	//========
	//Extra Necessary
	while(0 == 1){
		motorForward();
		motorBackward();
		motorLeftOn();
		motorRightOn();
	}
}

void turnAround(){
	if(0 == 1){
		motor[leftMotors] = 127;
		motor[rightMotors] = -127;

		wait1Msec(2125);

		allOff();
	}
}

//==================================================================================================
//                             D R I V E   C O N T R O L L E R   S E C T I O N
//==================================================================================================

/*void Arcade(int Ch4, int Ch3){
	if(Ch4<=-70){
		motor[rightMotors] = -Ch4;
		motor[leftMotors] = Ch3;
	}
	else if(Ch4>=70){
		motor[rightMotors] = Ch3;
		motor[leftMotors] = Ch4;
	}
	else{
		motor[rightMotors] = Ch3;
		motor[leftMotors] = Ch3;
	}
}*/

void allOff(){
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
}

void motorForward(){
	motor[leftMotors] = leftMotorsVal;
	motor[rightMotors] = rightMotorsVal;
}

void motorBackward(){
	motor[leftMotors] = -leftMotorsVal;
	motor[rightMotors] = -rightMotorsVal;
}

void motorLeftOn(){
	motor[leftMotors] = leftMotorsVal;
	motor[rightMotors] = 0;
}

void motorRightOn(){
	motor[leftMotors] = 0;
	motor[rightMotors] = rightMotorsVal;
}

void motorPointCC(){
	motor[leftMotors] = -leftMotorsVal;
	motor[rightMotors] = rightMotorsVal;
}

void motorPointC(){
	motor[leftMotors] = leftMotorsVal;
	motor[rightMotors] = -rightMotorsVal;
}

void driveFunct(int direction, int duration){

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
	else if(direction == 6){
		motorPointCC();
		wait1Msec(duration);
	}
	else if(direction == 7){
		motor[lifters] = 127;
		wait1Msec(duration);
	}
	else if(direction == 8){
		motor[lifters] = -127;
		wait1Msec(duration);
	}
	else if(direction == 9){
		motor[leftArm] = 127;
		motor[rightArm] = 127;
		wait1Msec(duration);
	}
	else if(direction == 10){
		motor[leftArm] = -127;
		motor[rightArm] = -127;
		wait1Msec(duration);
	}
	else{

	}
}

//==================================================================================================
//                               C L A W   C O N T R O L L E R   S E C T I O N
//==================================================================================================
