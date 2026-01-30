#include "main.h"
void wiggle(int speed){
	for(int i = 0; i < 17; i++ ){
		leftDrive.move(speed+5);
		rightDrive.move(-speed);
		pros::delay(100);
		leftDrive.move(-speed);
		rightDrive.move(speed+5);
		pros::delay(100);
	}

}
void pulseIntake(int fDelay, int bDelay,int intakeSpeed,int outtakeSpeed, int cycle){
	for(int i = 0; i < cycle; i++){
		moveBallPath(intakeSpeed,intakeSpeed,intakeSpeed,intakeSpeed);
		pros::delay(fDelay);
		moveBallPath(outtakeSpeed,outtakeSpeed,outtakeSpeed,outtakeSpeed);
		pros::delay(bDelay);
	}
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	chassis.reset();
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
	chassis.startTracking();
	chassis.moveDistance(33,10000,100);
	loaderPiston.extend();
	chassis.turnAngle(-90, 5000);
	moveBallPath(127,65,127,127); //intake from loader
	chassis.moveDistance(11,1000, 30);
	wiggle(20);
	chassis.turnAngle(-90,3000);
	moveBallPath(0,0,0,0);
	chassis.moveDistance(-30,3000, 30);
	moveBallPath(0,0,0,0);
	moveBallPath(0,-40,-40,-40); // dejam before scoring
	pros::delay(250);
	hoodPiston.extend();
	pulseIntake(350,50,127,-60,5); // score in long goal
	moveBallPath(127,127,127,127);
	pros::delay(1000);
	moveBallPath(0,0,0,0);
	chassis.moveDistance(15, 3000, 50);
	chassis.turnAngle(-45,3000);
	moveBallPath(127,-100,-100,-100); // outtake blue cubes
	hoodPiston.retract();
	pros::delay(2500);
	moveBallPath(0,0,0,0);
	chassis.turnAngle(-85,3000);
	moveBallPath(127,65,127,127); //intake from loader after refill
	chassis.moveDistance(12,3000);
	wiggle(20);
	chassis.turnAngle(-85,3000);
	moveBallPath(0,0,0,0);
	chassis.moveDistance(-30,3000, 30);
	moveBallPath(0,0,0,0);
	moveBallPath(0,-40,-40,-40); // dejam before scoring
	pros::delay(250);
	hoodPiston.extend();
	pulseIntake(350,50,127,-60,15); // score in long goal
	moveBallPath(127,127,127,127);
	pros::delay(1000);
	moveBallPath(0,0,0,0);
	loaderPiston.retract();
	wingPiston.extend();
	chassis.moveDistance(12,1000,30);
	chassis.turnAngle(-135,3000);
	chassis.moveDistance(-18,3000,30);
	chassis.turnAngle(-82,3000);
	wingPiston.extend();
	liftPiston.extend();
	hoodPiston.retract();
	chassis.moveDistance(-20,3000,75);


	
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
	int leftY, rightX;

	controller.clear();

	while (true) {
		leftY = controller.get_analog(ANALOG_LEFT_Y);
		rightX = controller.get_analog(ANALOG_RIGHT_X);
		chassis.arcade(leftY, rightX);

		intakePeriodic();

		if(controller.get_digital_new_press(DIGITAL_A)){
			autonomous();
		}

		pros::delay(20);
	}
}
