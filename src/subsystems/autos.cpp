#include "main.h"
#include <math.h>

float toRadians(float degrees) {
    return degrees * M_PI / 180.0;
}

void wiggle(int speed){
	for(int i = 0; i < 10; i++ ){
		leftDrive.move(speed);
		rightDrive.move(speed);
		pros::delay(100);
		leftDrive.move(0);
		rightDrive.move(0);
		pros::delay(100);
	}
    leftDrive.move(0);
    rightDrive.move(0);
}


void threeMidNineHigh(){
    chassis.setPose({1, 1, 0});
    chassis.startTracking();
//Move and pick up 2 blocks under goal
    intakeMotor.move(127);
    chassis.moveToPose({0, 51, 0}, 10000, 75);
//back out to the goal
    chassis.moveToPose({19.5, 25.5, 0}, 2000, 75);
    chassis.turnToAngle(90, 1500);
//move in and score
    chassis.moveToPose({50, 24.5, 0}, 300, 120);
    leverScoreMid(400, false); 
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
    chassis.moveToPose({-40, 12, 0}, 2000, 50);
    wiggle(30);
    chassis.turnToAngle(135, 500);
//eject opponent blocks
    // chassis.moveToPose({-28, 25.5, 0}, 10000, 75);
    // matchLoadPiston.retract();
    // chassis.turnToAngle(90, 1500);
    // liftPiston.retract();
    // intakeMotor.move(-100);
    // pros::delay(2000);
    intakeMotor.move(30);
    // chassis.turnToAngle(135, 1500);
    chassis.moveToPose({-17.5, 35, 0}, 10000, 75);

    leverScoreHigh(true);
    pros::delay(500);




    leverRetract();
}

void doNothing(){
    wingPiston.extend();
}

void fourHigh(){
    chassis.setPose(0, 0, 0);
    chassis.startTracking();
    wingPiston.extend();
    chassis.moveToPose({0, 32, 0}, 10000, 75);
    chassis.turnToAngle(90, 10000);
    intakeMotor.move(127);
    matchLoadPiston.extend();
    liftPiston.extend();
    chassis.moveToPose({-12, 31, 0}, 2000, 75);
    wiggle(50);
    chassis.moveToPose({30, 31, 0}, 2000, 75);
    matchLoadPiston.retract();
    intakeMotor.move(-50);
    pros::delay(1500);
    intakeMotor.move(30);
    leverScoreMid(300, false);
    pros::delay(1000);
    leverRetract();
    intakeMotor.move(-127);
    chassis.moveToPose({15, 20, 0}, 3000, 75);
    chassis.turnToAngle(90, 1000);
    wingPiston.retract();
    chassis.moveToPose({44, 22, 0}, 5000, 75);

    // pros::delay(5000);

}