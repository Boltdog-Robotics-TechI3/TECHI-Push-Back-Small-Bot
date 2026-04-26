#include "main.h"
#include "globals.hpp"
#include "lib/pid.hpp"
#include "pros/rtos.hpp"
#include "subsystems/intake.hpp"
#include <filesystem>
#include <string>
#include <iostream>


void wiggle(int speed, int wiggles){
	for(int i=0; i<wiggles; i++) {
		leftMotors.move(speed+5);
		rightMotors.move(-speed);
		pros::delay(100);	
		leftMotors.move(-speed);
		rightMotors.move(speed+5);
		pros::delay(100);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{

	initializeScreen();
	imu.reset(true);
	chassis.reset();
	intakeInitialize();
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {			
	// when making the auto make sure the speed is capped at 60% (127 *.6) so that
	// the robot doesn't go past the error range.
	// bug_test();
	// return;
	Pose matchLoadStation({-45.5, -64, 0});
	int smallTimeout = 500;
	int timeout = 1000;
	chassis.startTracking();
	matchLoader.retract();
	chassis.setPose({-14.5, -47.5, 3*M_PI_2});
	int maxSpeed = 127*0.6;
	int lowSpeed = 127 * 0.4;
	int overMax = 127 * 0.8;
	chassis.moveToPose({.targetPose = {-45.5, -47.5, 0}, .timeout = timeout, .maxMoveSpeed = maxSpeed});
	matchLoader.extend();
	lift.extend();
	hood.retract();
	hood.extend();
	chassis.turnToAngle({.targetAngle = 1, .timeout = smallTimeout + 50});

	intake.move(127);
	startCounting();
	chassis.moveToPose({.targetPose = matchLoadStation, .timeout = smallTimeout, .maxMoveSpeed = 127});
	wiggle(20, 2);

	pros::delay(300);
	if (blockCount <= 1) { // Adjust position if we're not getting blocks from the loader
		chassis.moveToPose({.targetPose = {-47, -58.5, 0}});
		controller.set_text(0, 0, std::to_string(blockCount));
		pros::delay(100);
	}

	chassis.moveToPose({.targetPose = {-47, -27, 0}, .timeout = timeout, .maxMoveSpeed = maxSpeed}); //goto score
	wiggle(40, 4);


	chassis.turnToAngle({.targetAngle = 1, .timeout = smallTimeout});
	pros::delay(100);

	fire();
	while (firing) { pros::delay(20); };

	intake.brake();

	chassis.moveToPose({.targetPose = {-47, -47.5, 0}, .timeout = 800, .maxMoveSpeed = maxSpeed});
	chassis.turnToAngle({.targetAngle = 315, .timeout = smallTimeout});
	chassis.moveToPose({.targetPose = {-35.5, -11.5, 0}, .timeout = timeout, .maxMoveSpeed = maxSpeed});
	chassis.turnToAngle({.targetAngle = 0, .timeout = smallTimeout});
	lift.retract();
	matchLoader.retract();
	chassis.moveToPose({.targetPose = {-35.5, 0, 0}});
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
 
void opcontrol() {
	chassis.startTracking();
	matchLoader.retract();
	startCounting();
	
	while(true) {
		int throttle = controller.get_analog(ANALOG_LEFT_Y);
		int turn = controller.get_analog(ANALOG_RIGHT_X);
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
			chassis.arcade(throttle*0.45,turn*0.45);
		} else{
			chassis.arcade(throttle,turn);
		}
		//controller.set_text(0,0,std::to_string(blockCount));
		intakePeriodic();
		pros::delay(20);
	}
}
