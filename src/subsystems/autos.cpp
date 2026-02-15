#include "main.h"
#include <math.h>

float toRadians(float degrees) {
    return degrees * M_PI / 180.0;
}

void wiggle(int speed){
	for(int i = 0; i < 10; i++ ){
		leftDrive.move(speed+10);
		rightDrive.move(-speed);
		pros::delay(100);
		leftDrive.move(-speed);
		rightDrive.move(speed+10);
		pros::delay(100);
	}
    leftDrive.move(0);
    rightDrive.move(0);
}


void threeMidNineHigh(){
    chassis.setPose({0, 0, 0});
//Move and pick up 2 blocks under goal
    intakeMotor.move(127);
    chassis.moveToPose({0, 51, 0}, 10000, 75);
//back out to the goal
    chassis.moveToPose({19.5, 25.5, 0}, 2000, 75);
    chassis.turnToAngle(90, 1500);
//move in and score
    chassis.moveToPose({50, 25.5, 0}, 300, 120);
    leverScoreMid(400); 
    pros::delay(500);
    leverRetract();
//go to load station
    intakeMotor.move(0);
    chassis.moveToPose({-28, 25.5, 0}, 10000, 75);
    chassis.turnToAngle(135, 1500);
    matchLoadPiston.extend();
    intakeMotor.move(100);
    liftPiston.extend();
//start intaking from loader
    chassis.moveToPose({-40, 12, 0}, 3500, 50);
    chassis.turnToAngle(135, 500);
//eject opponent blocks
    chassis.moveToPose({-28, 25.5, 0}, 10000, 75);
    matchLoadPiston.retract();
    chassis.turnToAngle(90, 1500);
    intakeMotor.move(-100);
    pros::delay(1000);
    intakeMotor.move(30);
    chassis.turnToAngle(135, 1500);
    chassis.moveDistance(-15, 2000);
    leverScoreHigh(true);
    pros::delay(500);





}

void doNothing(){}