#include "main.h"

void wiggle(int speed){
	for(int i=0; i<20; i++)
		leftMotors.move(speed+5);
		rightMotors.move(-speed);
		pros::delay(100);	
		leftMotors.move(-speed);
		rightMotors.move(speed+5);
		pros::delay(100);
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
	chassis.startTracking();
	matchLoader.retract();
	chassis.setPose({22, -42, M_PI/2});
	double maxSpeed = 127*0.6;
	chassis.moveToPose({54, -42, M_PI/2}, 5000, maxSpeed);
	matchLoader.extend();
	chassis.turnToAngle(0, 5000);
	intake.move(127);
	chassis.moveToPose({54, -57, 0}, 1000, 127);
	lift.extend();
	chassis.moveToPose({54, -36, 0}, 2000, maxSpeed);
	intake.move(0);
	chassis.turnToAngle(0, 5000);
	//not aligning with the goal, fix for later
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
	while(true) {
		int throttle = controller.get_analog(ANALOG_LEFT_Y);
		int turn = controller.get_analog(ANALOG_RIGHT_X);
		chassis.arcade(throttle,turn);
		intakePeriodic();
		controller.set_text(0,0,(chassis.getPose().to_string()));
		pros::delay(20);
		
    }
}
