#pragma config(Sensor, in1,    potSensor,      sensorPotentiometer)
#pragma config(Sensor, in2,    rightLiftSensor, sensorPotentiometer)
#pragma config(Sensor, in3,    leftLiftSensor, sensorPotentiometer)
#pragma config(Sensor, dgtl7,  ArmLimit,       sensorTouch)
#pragma config(Sensor, dgtl8,  ElbowLimit,     sensorTouch)
#pragma config(Sensor, dgtl9,  RightBottomEnc, sensorQuadEncoder)
#pragma config(Sensor, dgtl11, LeftBottomEnc,  sensorQuadEncoder)
#pragma config(Motor,  port2,           leftMotors,    tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port3,           rightMotors,   tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port4,           leftArm,       tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port5,           rightArm,      tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port6,           lifters,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           elbow,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           claw,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

//Motor on values
static int leftMotorsVal = 127;
static int rightMotorsVal = 127;
static int initRightEncoder = 0;
static int initLeftEncoder = 0;


//Central Functions Section
void controllerBasic();

//Drive Controller Section
void resetEncoders();
void updatePowers();
void driveUntil(int right, int left);
void compAuton();
void skillsAuton();
void setupAuton();
void pushLifter();

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

	//SKILLS:
	if(SensorValue[potSensor] < 2000){
		skillsAuton();
	}

	//COMP:
	else {
		compAuton();
	}
}

task usercontrol(){
	while (true){
		controllerBasic();
	}
}

//==================================================================================================
//                           C E N T R A L   F U N C T I O N S   S E C T I O N
//--------------------------------------------------------------------------------------------------
//			MAIN FUNCTIONS:
//				1. CONTROLLER BASIC (120)
//				2. DRIVE FUNCT (263)
//				3. DRIVE UNTIL (336)
//				4. COMP AUTON (394)
//				5. SKILLS AUTON (426)
//
//			CONTROLLER INDEX:
//				1. DRIVE CONTROLLER SECTION (217)
//				2. ENCODER CONTROLLER SECTION (305)
//				3. AUTONOMOUS CONTROLLER SECTION (391)
//==================================================================================================

void controllerBasic(){

	//========
	//BASE
	if(vexRT[Btn8U] == 1) {
		resetEncoders();
	}
	else if(vexRT[Btn8L] == 1) { //test button for competition autonomous
		compAuton();
	}
	else if(vexRT[Btn8R] == 1) {
		skillsAuton();
	}
	else if(vexRT[Btn8D] == 1) {
		motor[leftMotors] = -127;
		motor[rightMotors] = -45;
		wait1Msec(2200);
		resetEncoders();
		motor[leftMotors] = -127;
		motor[rightMotors] = 127;
		wait1Msec(1000);
		motor[leftMotors] = 127;
		motor[rightMotors] = 127;
		wait1Msec(2000);
		motor[leftMotors] = 0;
		motor[rightMotors] = 0;
		while(SensorValue[leftLiftSensor] > 1374 || SensorValue[rightLiftSensor] > 3050) {
			motor[lifters] = -127;
		}
		motor[lifters] = 20;
		motor[leftMotors] = -127;
		motor[rightMotors] = -127;
		wait1Msec(1000);
		motor[lifters] = 0;
		motor[leftMotors] = 0;
		motor[rightMotors] = 0;

	}
	else if(vexRT[Btn7U] == 1) {
		//FORWARD
	}
	else if(vexRT[Btn7D] == 1) {
		//BACKWARD
	}
	else if(vexRT[Btn7L] == 1) {
		//COUNTER CLOCKWISE
	}
	else if(vexRT[Btn7R] == 1) {
		//CLOCKWISE
	}
	else {
		motor[leftMotors] = vexRT(Ch3);
		motor[rightMotors] = vexRT(Ch2);
	}

	//========
	//LIFTERS
	if(vexRT[Btn5U] == 1 || vexRT[Btn5UXmtr2] == 1){
		if(SensorValue[leftLiftSensor] < 1950 || SensorValue[rightLiftSensor] < 3850) { //values ensure lifters don't sratch motor
			motor[lifters] = 127;
		}
		else {
			motor[lifters] = 0;
		}
	}
	else if(vexRT[Btn5D] == 1 || vexRT[Btn5DXmtr2] == 1){
		if(SensorValue[leftLiftSensor] > 940 || SensorValue[rightLiftSensor] > 2550) { //values ensure lifters don't sratch floor
			motor[lifters] = -127;
		}
		else {
			motor[lifters] = 0;
		}
	}
	else if(vexRT[Btn8D] == 1) {
		pushLifter();
	}
	else{
		motor[lifters] = 0;
	}

	//========
	//ARMS
	if(SensorValue[ArmLimit] == 1 && vexRT(Ch3Xmtr2) > 0) { //if sensor is pressed and arm is not to move down
		motor[leftArm] = 0;
		motor[rightArm] = 0;
	}
	else if(vexRT(Ch3Xmtr2) > 10 || vexRT(Ch3Xmtr2) < -10){
		if(SensorValue[leftLiftSensor] > 1808 || SensorValue[rightLiftSensor] > 3550)  {
			motor[lifters] = -127;
			motor[leftArm] = 0;
			motor[rightArm] = 0;
		}
		else {
			motor[leftArm] = vexRT(Ch3Xmtr2);
			motor[rightArm] = vexRT(Ch3Xmtr2);
		}
	}
	else {
		motor[leftArm] = 0;
		motor[rightArm] = 0;
	}

	//=========
	//ELBOW
	if(SensorValue[ElbowLimit] == 1 && vexRT(Ch2Xmtr2) > 0) { //if sensor is pressed and elbow is not to move down
		motor[elbow] = 0;
	}
	else {
		motor[elbow] = vexRT(Ch2Xmtr2);
	}

	//=========
	//CLAW
	if(vexRT[Btn6UXmtr2] == 1 || vexRT[Btn6U] == 1){
		motor[claw] = 127; //this opens claw
	}
	else if(vexRT[Btn6DXmtr2] == 1 || vexRT[Btn6D] == 1){
		motor[claw] = -127; //this closes claw
	}
	else{
		motor[claw] = 0;
	}
}

//==================================================================================================
//                             D R I V E   C O N T R O L L E R   S E C T I O N
//==================================================================================================

//==================================================================================================
//                             E N C O D E R   C O N T R O L L E R   S E C T I O N
//==================================================================================================

void resetEncoders() { //reset both encoder values
	SensorValue[RightBottomEnc] = 0;
	SensorValue[LeftBottomEnc] = 0;
}

void updatePowers() {
	int cp = 7; //estimated corrective proportion, translates the offset of encoder values into the amount of power a motor needs to adjust
	int right = abs(SensorValue[RightBottomEnc]); //absolute value of right encoder
	int left = abs(SensorValue[LeftBottomEnc]); //absolute value of left encoder
	if(right > left) {
		//if the right motor is overpowered
		//decrease right motor power by the difference in encoder values times cp
		leftMotorsVal = 127;
		if(rightMotorsVal > 10+(int)(cp*(right - left))) {
			rightMotorsVal = rightMotorsVal - (int)(cp*(right - left));
		}
	}
	else if(right < left){
		//if the left motor is overpowered
		//decrease left motor power by the difference in encoder values times cp
		rightMotorsVal = 127;
		if(rightMotorsVal > 10+(int)(cp*(left - right))) {
			leftMotorsVal = leftMotorsVal - (int)(cp*(left - right));
		}
	}
	//if the motors are of equal strength, motor powers don't change
}

void driveUntil(int right, int left) { //target number of ticks from right and left encoder
	resetEncoders();
	int curRight = 0; //total number of ticks from right encoder
	int curLeft = 0; //total number of ticks from left encoder
	while(abs(curRight) < abs(right) || abs(curLeft) < abs(left)) { //while target numbers are not met
		updatePowers();
		if(abs(curRight) < abs(right)) {
			//if right target is not met
			//turn the motor on certain direction to reach target value
			if(right > 0) {
				motor[rightMotors] = rightMotorsVal;
			}
			else if(right < 0) {
				motor[rightMotors] = -rightMotorsVal;
			}
			else {
				motor[rightMotors] = 0;
			}
		}
		else {
			motor[rightMotors] = 0;
		}
		if(abs(curLeft) < abs(left)) {
			//if left target is not met
			//turn the motor on certain direction to reach target value
			if(left > 0) {
				motor[leftMotors] = leftMotorsVal;
			}
			else if(left < 0) {
				motor[leftMotors] = -leftMotorsVal;
			}
			else {
				motor[leftMotors] = 0;
			}
		}
		else {
			motor[leftMotors] = 0;
		}
		//update current number of ticks before resetting encoders
		curRight = curRight + SensorValue[RightBottomEnc];
		curLeft = curLeft + SensorValue[LeftBottomEnc];
		resetEncoders();
	}
	allMotorsOff();
}

//==================================================================================================
//                      A U T O N O M O U S   C O N T R O L L E R   S E C T I O N
//==================================================================================================

void compAuton() {
	setupAuton();
	while(SensorValue[leftLiftSensor] > 1680 || SensorValue[rightLiftSensor] > 3200) {
		motor[lifters] = 127;
	}
	motor[lifters] = 0;
	motor[leftMotors] = 127;
	motor[rightMotors] = -127;
	wait1Msec(65);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	driveUntil(775,775);
	motor[leftMotors] = 127;
	motor[rightMotors] = -127;
	wait1Msec(85);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	driveUntil(775,775);
	driveUntil(-350,-350);
	motor[leftMotors] = -127;
	motor[rightMotors] = 127;
	wait1Msec(222);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	while(SensorValue[leftLiftSensor] > 940 || SensorValue[rightLiftSensor] > 2550) {
		motor[lifters] = -127;
	}
	motor[lifters] = 0;
	driveUntil(305,305);
	wait1Msec(100);
	while(SensorValue[leftLiftSensor] < 1950 || SensorValue[rightLiftSensor] < 3850) {
		motor[lifters] = 127;
	}
	motor[lifters] = 0;
	driveUntil(-350,-350);
	motor[leftMotors] = 127;
	motor[rightMotors] = -127;
	wait1Msec(175);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	driveUntil(-1000,-1000);
	motor[leftMotors] = -127;
	motor[rightMotors] = 127;
	wait1Msec(500);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	driveUntil(-90,-90);
	motor[leftMotors] = -127;
	motor[rightMotors] = 127;
	wait1Msec(725);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	motor[leftMotors] = 127;
	motor[rightMotors] = 127;
	wait1Msec(1600);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	while(SensorValue[leftLiftSensor] > 1374 || SensorValue[rightLiftSensor] > 3050) {
		motor[lifters] = -127;
	}
	motor[lifters] = 20;
	motor[leftMotors] = -127;
	motor[rightMotors] = -127;
	wait1Msec(1000);
	motor[lifters] = 0;
	motor[leftMotors] = 0;


	/*
	setupAuton();
	//---DRIVE UNTIL PROXIMITY ALLOWS FOR CONE DROP---//
	driveUntil(800,800);
	//---LOWER ELBOW---//
	motor[elbow] = -127;
	wait1Msec(300); //850 when in low power, 300 when full power
	motor[elbow] = 0;
	wait1Msec(500);
	//---DROP CONE---//
	motor[claw] = 127;
	wait1Msec(500);
	//---RAISE CLAW---//
	motor[elbow] = 127;
	wait1Msec(1250);
	motor[claw] = 0;
	motor[elbow] = 0;
	//---ENSURE LIFTERS ARE LOWERED---//
	while(SensorValue[leftLiftSensor] > 940 || SensorValue[rightLiftSensor] > 2550) {
		motor[lifters] = -127;
	}
	motor[lifters] = 0;
	//---MOVE FORWARD TO PICK GOAL UP---//
	driveUntil(-100,-100);
	motor[leftMotors] = 127;
	motor[rightMotors] = 127;
	wait1Msec(1750);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	//---RAISE LIFTERS---//
	while(SensorValue[leftLiftSensor] < 1950 || SensorValue[rightLiftSensor] < 3850) {
		motor[lifters] = 127;
	}
	motor[lifters] = 0;
	//---DRIVE BACK---//
	motor[leftMotors] = -127;
	motor[rightMotors] = -127;
	wait1Msec(1750);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	motor[leftMotors] = -127;
	motor[rightMotors] = -45;
	wait1Msec(3300); //2300 when low on power, 3300 when high on power
	resetEncoders();
	motor[leftMotors] = -127;
	motor[rightMotors] = 127;
	wait1Msec(810); //1000 when low on power, 810 when high on power
	motor[leftMotors] = 127;
	motor[rightMotors] = 127;
	wait1Msec(1400);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	while(SensorValue[leftLiftSensor] > 1374 || SensorValue[rightLiftSensor] > 3050) {
		motor[lifters] = -127;
	}
	motor[lifters] = 20;
	motor[leftMotors] = -127;
	motor[rightMotors] = -127;
	wait1Msec(1000);
	motor[lifters] = 0;
	motor[leftMotors] = 0;
	motor[rightMotors] = 0; */
	allMotorsOff();
}

void skillsAuton() {
	//setupAuton();
	driveUntil(750,700);
	//---RAISE LIFTERS---//
	while(SensorValue[leftLiftSensor] < 1950 || SensorValue[rightLiftSensor] < 3850) {
		motor[lifters] = 127;
	}
	motor[lifters] = 0;
	driveUntil(-500,-500);
	motor[leftMotors] = 127;
	motor[rightMotors] = -127;
	wait1Msec(810); //1000 when low on power, 810 when high on power
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	driveUntil(250,250);
	motor[leftMotors] = 127;
	motor[rightMotors] = -127;
	wait1Msec(810); //1000 when low on power, 810 when high on power
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	motor[leftMotors] = 127;
	motor[rightMotors] = 127;
	wait1Msec(1600);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	while(SensorValue[leftLiftSensor] > 1374 || SensorValue[rightLiftSensor] > 3050) {
		motor[lifters] = -127;
	}
	motor[lifters] = 20;
	motor[leftMotors] = -127;
	motor[rightMotors] = -127;
	wait1Msec(1000);
	motor[lifters] = 0;
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	motor[leftMotors] = -127;
	motor[rightMotors] = 127;
	wait1Msec(770); //1000 when low on power, 770 when high on power
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	driveUntil(200,200);
	while(SensorValue[leftLiftSensor] > 940 || SensorValue[rightLiftSensor] > 2550) {
		motor[lifters] = -127;
	}
	motor[lifters] = 0;
	motor[leftMotors] = -127;
	motor[rightMotors] = 127;
	wait1Msec(770); //1000 when low on power, 770 when high on power
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	driveUntil(550,550);
	while(SensorValue[leftLiftSensor] < 1950 || SensorValue[rightLiftSensor] < 3850) {
		motor[lifters] = 127;
	}
	motor[lifters] = 0;
	motor[leftMotors] = 127;
	motor[rightMotors] = -127;
	wait1Msec(1540); //2000 when low on power, 1540 when high on power
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	driveUntil(770,770);
	while(SensorValue[leftLiftSensor] > 940 || SensorValue[rightLiftSensor] > 2550) {
		motor[lifters] = -127;
	}
	motor[lifters] = 40;
	wait1Msec(100);
	motor[leftMotors] = -127;
	motor[rightMotors] = -127;
	wait1Msec(1000);
	motor[lifters] = 0;
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	motor[leftMotors] = -127;
	motor[rightMotors] = 127;
	wait1Msec(1540); //2000 when low on power, 1540 when high on power
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	driveUntil(725,725);
	while(SensorValue[leftLiftSensor] < 1950 || SensorValue[rightLiftSensor] < 3850) {
		motor[lifters] = 127;
	}
	motor[lifters] = 0;

	//***REPEAT AGAIN***//
	driveUntil(250,250);
	motor[leftMotors] = 127;
	motor[rightMotors] = -127;
	wait1Msec(810); //1000 when low on power, 810 when high on power
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	motor[leftMotors] = 127;
	motor[rightMotors] = 127;
	wait1Msec(1600);
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	while(SensorValue[leftLiftSensor] > 1374 || SensorValue[rightLiftSensor] > 3050) {
		motor[lifters] = -127;
	}
	motor[lifters] = 20;
	motor[leftMotors] = -127;
	motor[rightMotors] = -127;
	wait1Msec(1000);
	motor[lifters] = 0;
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	motor[leftMotors] = -127;
	motor[rightMotors] = 127;
	wait1Msec(770); //1000 when low on power, 770 when high on power
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	driveUntil(200,200);
	while(SensorValue[leftLiftSensor] > 940 || SensorValue[rightLiftSensor] > 2550) {
		motor[lifters] = -127;
	}
	motor[lifters] = 0;
	motor[leftMotors] = -127;
	motor[rightMotors] = 127;
	wait1Msec(770); //1000 when low on power, 770 when high on power
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	driveUntil(550,550);
	while(SensorValue[leftLiftSensor] < 1950 || SensorValue[rightLiftSensor] < 3850) {
		motor[lifters] = 127;
	}
	motor[lifters] = 0;
	motor[leftMotors] = 127;
	motor[rightMotors] = -127;
	wait1Msec(1540); //2000 when low on power, 1540 when high on power
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;
	driveUntil(770,770);
	while(SensorValue[leftLiftSensor] > 940 || SensorValue[rightLiftSensor] > 2550) {
		motor[lifters] = -127;
	}
	motor[lifters] = 40;
	wait1Msec(100);
	motor[leftMotors] = -127;
	motor[rightMotors] = -127;
	wait1Msec(1000);
	motor[lifters] = 0;
	motor[leftMotors] = 0;
	motor[rightMotors] = 0;

	allMotorsOff();
}

void setupAuton() {
	resetEncoders();
	//---EXTEND LIFTERS---//
	while(SensorValue[leftLiftSensor] > 940 || SensorValue[rightLiftSensor] > 2550) { //1556 3266
		//while lifters are not fully extended, extend lifters
		motor[lifters] = -127;
	}
	motor[lifters] = 0;
	//---RAISE ARM TO ALLOW ELBOW TO EXTEND---//
	motor[rightArm] = 127;
	motor[leftArm] = 127;
	wait1Msec(1100); //1500 when low on power, 1100 when high
	motor[rightArm] = 0;
	motor[leftArm] = 0;
	//---RAISE ELBOW---//
	motor[elbow] = 127;
	wait1Msec(1300); //1500 when low on power, 1300 when high
	motor[elbow] = 0;
	//---LOWER ARM---//
	motor[claw] = -127;
	motor[rightArm] = -127;
	motor[leftArm] = -127;
	wait1Msec(500);
	motor[claw] = 0;
	motor[rightArm] = 127;
	motor[leftArm] = 127;
	wait1Msec(250);
	motor[rightArm] = -127;
	motor[leftArm] = -127;
	wait1Msec(200);
	motor[rightArm] = 0;
	motor[leftArm] = 0;
}

void pushLifter() {
	while(SensorValue[leftLiftSensor] > 1374 || SensorValue[rightLiftSensor] > 3050) {
		motor[lifters] = -127;
	}
	while(SensorValue[leftLiftSensor] < 2025 || SensorValue[rightLiftSensor] < 3800) {
		motor[lifters] = 127;
	}
	motor[lifters] = 0;
}
