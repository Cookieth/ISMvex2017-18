#pragma config(Sensor, dgtl1,    limitSwitch,  sensorTouch)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           backRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           frontMangonel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           backMangonel,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           claw,          tmotorVex393_MC29, openLoop)

#pragma platform(VEX2)
#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"

void basicAutonomous();
void nAutonomous();

void pre_auton()
{
  bStopTasksBetweenModes = true;
}

task autonomous()
{
	basicAutonomous();
}

task usercontrol()
{
	int driveGear = 1;
	int direction = 1;
	
//---------------------------------------------------------------------------------------------------------------
//
//																D R I V E R  C O N T R O L   S E C T I O N
//---------------------------
// Functions
//---------------------------
//
//--------------------------- 
// Controller 1 
//---------------------------
// AccelX
// AccelY
// AccelZ
// Btn5U
// Btn5D
// Btn6U
// Btn6D
// Btn7U
// Btn7D
// Btn7L
// Btn7R
// Btn8U
// Btn8D
// Btn8L
// Btn8R
// Ch1
// Ch2: Right-Side Base Motors
// Ch3: Left-Side Base Motors
// Ch4
//---------------------------
// Controller 2
//---------------------------
// AccelXXmtr2
// AccelYXmtr2
// AccelZXmtr2
// Btn5UXmtr2
// Btn5DXmtr2
// Btn6UXmtr2
// Btn6DXmtr2
// Btn7UXmtr2
// Btn7DXmtr2
// Btn7LXmtr2
// Btn7RXmtr2
// Btn8UXmtr2
// Btn8DXmtr2
// Btn8LXmtr2
// Btn8RXmtr2
// Ch1Xmtr2
// Ch2Xmtr2
// Ch3Xmtr2
// Ch4Xmtr2
//---------------------------------------------------------------------------------------------------------------
  while (true)
    {
    	int trueCh2 = (vexRT[Ch2]*direction)/driveGear;
    	int trueCh3 = (vexRT[Ch3]*direction)/driveGear;
    	
    	if(direction == 1){
      	motor[frontRight] = trueCh2;
      	motor[backRight] = trueCh2;
      	motor[frontLeft] = trueCh3;
      	motor[backLeft] = trueCh3;
  		}
  		else{
  			motor[frontRight] = trueCh3;
      	motor[backRight] = trueCh3;
      	motor[frontLeft] = trueCh2;
      	motor[backLeft] = trueCh2;
  		}
  		
      if(vexRT[Btn8U]==1) {
       motor[frontMangonel] = 100;
       motor[backMangonel] = 100;
      }
      else if(vexRT[Btn8D] == 1) {
       if(SensorValue[limitSwitch] != 1) {
          motor[frontMangonel] = 80;
          motor[backMangonel] = 80;
       }
      }
      else {
       motor[frontMangonel] = 0;
       motor[backMangonel] = 0;
      }
  
      //===========================================
      //					RIGHT SIDE OF THE REMOTE
      //===========================================
      
      if(vexRT[Btn7L] == 1) {
       motor[intake] = 127;
       wait1Msec(0310);
       motor[intake] = 0;
       wait1Msec(0500);
      }
      else if(vexRT[Btn7R] == 1) {
       motor[intake] = -127;
       wait1Msec(0310);
       motor[intake] = 0;
       wait1Msec(0500);
      }
      else {
       motor[intake] = 0;
      }
      
      if(vexRT[Btn7U] == 1) {
       direction = direction * -1;
       wait1Msec(0500);
      }
      
      if(vexRT[Btn5U] == 1) {
       motor[intake] = 20; //ADJUSTABLE
      }
      else if(vexRT[Btn5D] == 1) {
       motor[intake] = -20; //ADJUSTABLE
      }
      else {
       motor[intake] = 0;
      }
  
      //===========================================
      //					RIGHT SIDE OF THE REMOTE
      //===========================================
      if(vexRT[Btn6D] == 1) {
          motor[claw] = 100;
      }
      else if(vexRT[Btn6U] == 1) {
          motor[claw] = -100;
      }
      else {
          motor[claw] = 0;
      }
      
      if(vexRT[Btn8R] == 1) {
      	driveGear += 1;
      	wait1Msec(0500);
    	}
    	else if((vexRT[Btn8L] == 1)&&(driveGear > 1)){
    		driveGear -= 1;
    		wait1Msec(0500);
    	}
    }
}

//---------------------------------------------------------------------------------------------------------------
//
//                                A U T O N O M O U S   C O N T R O L   S E C T I O N
//														Functions:
//																basicAutonomous - Simple sutonomous code
//																nAutonomous - Template autonomous code
//
//---------------------------------------------------------------------------------------------------------------

void basicAutonomous(){
  motor[backLeft] = 127;
  motor[backRight] = 127;
  wait1Msec(2000);
  motor[backLeft] = -127;
  motor[backRight] = -127;
  wait1Msec(1000);
  motor[backLeft] = 127;
  motor[backRight] = 0;
  wait1Msec(1000);
  motor[backLeft] = 127;
  motor[backRight] = 127;
  wait1Msec(2000);
  motor[backLeft] = 0;
  motor[backRight] = 0;
  wait1Msec(2000);
  
  motor[frontMangonel] = 0;
  motor[backMangonel] = 0;
}

void nAutonomous(){
	
}
