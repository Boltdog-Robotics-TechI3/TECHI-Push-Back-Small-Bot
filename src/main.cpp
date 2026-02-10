#include "main.h"

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
			// chassis.moveDistance(16,1500);
			// chassis.turnAngle(270,1500);
			// MatchLoader.extend();
			// hood.extend(); 
			// bottomIntakeMotors.move(-127);
			// chassis.moveDistance(900,3400);
			// // wiggle(40);

			// // wiggle(40);
			// // wiggle(40);
			// chassis.moveDistance(1500,1500);
			// // wiggle(40);
			// // wiggle(40);
			// pros::delay(2500);
			// bottomIntakeMotors.move(0);
			// chassis.moveDistance(-5,500);
			// chassis.turnAngle(-350,1500);

			// MatchLoader.retract();
			// chassis.moveDistance(35,2000);
			// intakeMotors.move(-127);
			// pros::delay(2500);
			// intakeMotors.move(0);



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
void wiggle(int speed){
	for(int i=0; i<20; i++)
	leftMotors.move(speed+5);
	rightMotors.move(-speed);
	pros::delay(100);	
	leftMotors.move(-speed);
	rightMotors.move(speed+5);
	pros::delay(100);
}
 
void opcontrol()
{
	chassis.startTracking();
	while(true) {
		
		int throttle = controller.get_analog(ANALOG_LEFT_Y);
		int turn = controller.get_analog(ANALOG_RIGHT_X);
		chassis.arcade(throttle,turn);
		intakePeriodic();
		controller.set_text(0,0,std::to_string(chassis.getPose().getTheta()));
		pros::delay(20);
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X))
    {			chassis.turnToAngle(90,1500);
				chassis.turnToAngle(-90,1500);
	}
	if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A))
	
    {
    			chassis.moveDistance(16,1500);
			// chassis.turnToAngle(90,1500);
			// MatchLoader.extend();
			// hood.extend(); 
			// bottomIntakeMotors.move(-127);
			// chassis.moveDistance(900,3400);
			// wiggle(40);


			// wiggle(40);
			// wiggle(40);
			// chassis.moveDistance(1500,1500);
			// wiggle(40);
			// wiggle(40);
			// pros::delay(2500);
			// bottomIntakeMotors.move(0);
			// chassis.moveDistance(-5,500);
			// chassis.turnToAngle(-90,1500);

			// MatchLoader.retract();
			// chassis.moveDistance(35,2000);
			// intakeMotors.move(-127);
			// pros::delay(2500);
			// intakeMotors.move(0);

    }

	}
}