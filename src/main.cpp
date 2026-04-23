#include "main.h"
#include "globals.hpp"
#include "subsystems/intake.hpp"
#include <string>


void wiggle(int speed){
	for(int i=0; i<10; i++) {
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
	Pose matchLoadStation({47, -63, 0});
	chassis.startTracking();
	matchLoader.retract();
	chassis.setPose({14.5, -47.5, M_PI_2});
	int maxSpeed = 127*0.6;
	int lowSpeed = 127 * 0.4;
	chassis.moveToPose({.targetPose = {46, -47.5, 0}, .timeout = 5000, .maxMoveSpeed = maxSpeed});
	matchLoader.extend();
	lift.extend();
	chassis.turnToAngle({.targetAngle = 0});
	hood.extend();
	//startCounting();
	intake.move(127);
	chassis.moveToPose({.targetPose = matchLoadStation, .timeout = 1000, .maxMoveSpeed = 127});
	//int time = pros::c::millis();
	// while (blockCount < 3) {
	// 	pros::delay(25); 
	// 	//timeout
	// 	if (pros::c::millis() - time < 5000)
	// 		break;
	// }
	pros::delay(1000);
	//controller.set_text(0,0, std::to_string(blockCount));
	chassis.moveToPose({.targetPose = {47, -28.5, 0}, .timeout = 2000, .maxMoveSpeed = maxSpeed}); //goto score
	wiggle(10);
	// intake.move(0);
	chassis.turnToAngle({.targetAngle = 0, .timeout = 1000});

	fire(false);

	// //go back to get the rest of the blocks
	pros::delay(3000);

	matchLoader.extend();
	chassis.moveToPose({.targetPose = matchLoadStation, .timeout = 3000, .maxMoveSpeed = lowSpeed});
	pros::delay(2500);

	// Throw other alliance blocks in the corner
	chassis.moveToPose({.targetPose = {47, -49.5, 0}, .timeout = 2500, .maxMoveSpeed = maxSpeed});
	chassis.turnToAngle({.targetAngle = 225, .timeout = 2000});
	hood.extend();
	fire(false);
	pros::delay(3000);

	// Go back to match load
	chassis.turnToAngle({.targetAngle = 0, .timeout = 1000});
	chassis.moveToPose({.targetPose = matchLoadStation, .timeout = 3000, .maxMoveSpeed = lowSpeed});
	pros::delay(5000);

	// TODO: Score remaining blocks
	chassis.moveToPose({.targetPose = {47, -28.5, 0}, .timeout = 2000, .maxMoveSpeed = maxSpeed});
	controller.set_text(0, 0, chassis.getPose().to_string());
	intake.move(0);


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
		chassis.arcade(throttle,turn);
		controller.set_text(0,0,std::to_string(blockCount));
		intakePeriodic();
		pros::delay(20);
	}
}
