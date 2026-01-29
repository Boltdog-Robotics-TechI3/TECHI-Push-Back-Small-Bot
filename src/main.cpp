#include "main.h"
#include "main.h"


// Bot measurements
float wheel_diameter = 3.25;
float track_width = 12.5;
float gear_ratio = 3.0/4.0;

// Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Motor Groups
pros::MotorGroup rightMotors({11, 12, -13});
pros::MotorGroup leftMotors({18, -19, -20});

// Drivetrain
DifferentialDrivetrain drivetrain(&leftMotors, &rightMotors, wheel_diameter, track_width, gear_ratio);

// Tracking Wheel
pros::IMU imu(15);

TrackingWheel horizontalTrackingWheel(-17, 2.08, -1, WheelPosition::BACK);
TrackingWheel verticalTrackingWheel(-16, 2.08, 1.875, WheelPosition::LEFT);

// Odometry
Odometry odometry(&verticalTrackingWheel, nullptr, &horizontalTrackingWheel, &imu);

// Chassis PID Controllers
PIDController lateral(8, 0, 0.1); 
PIDController turn(60, 0.2, 3);
PIDController align(30, 0, 0);

// Chassis
DifferentialChassis chassis(&drivetrain, &odometry, &lateral, &turn, &align);

// Pure Pursuit Controller
PurePursuitController autoBuilder(&chassis, 6, 5.0); 

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	chassis.reset();
	chassis.setPose(0, 0, Pose::degToRad(0));
	chassis.startTracking();
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
		
	// Trajectory testTrajectory = TrajectoryGenerator::generateTrajectory({
	// 	Pose(0, 0, Pose::degToRad(0)),
	// 	Pose(-5, 15, Pose::degToRad(0)),
	// 	// Pose(6, 18, Pose::degToRad(0)),
	// 	Pose(5, 28, Pose::degToRad(-90))
	// });
	// intakeMotors.move(100);
	// Trajectory testTrajectory = TrajectoryGenerator::generateTrajectory({
	// 	Pose(0, 0, Pose::degToRad(0)),
	// 	// Pose(6, 18, Pose::degToRad(0)),
	// 	Pose(0, 24, Pose::degToRad(-45)),
	// 	Pose(-48, 36, Pose::degToRad(-45)),
	// 	// Pose(-52, 60, Pose::degToRad(0)),
	// 	Pose(-54, 100, Pose::degToRad(0)),
	// 	// Pose(6, 80, Pose::degToRad(135)),
	// 	// Pose(12, 36, Pose::degToRad(180))

	// });

	// Trajectory testBackwardsTrajectory = TrajectoryGenerator::generateTrajectory({
	// 	Pose(-54, 100, Pose::degToRad(0)),
	// 	Pose(-48, 36, Pose::degToRad(-45)),
	// 	Pose(0, 24, Pose::degToRad(-45)),
	// 	Pose(0, 0, Pose::degToRad(0))
	// });

	// Trajectory testBackwardsTrajectory = TrajectoryGenerator::generateTrajectory({
	// 	Pose(0, 0, Pose::degToRad(0)),
	// 	Pose(12, -24, Pose::degToRad(-45)),
	// 	Pose(24, -36, Pose::degToRad(0)),
	// 	// Pose(0, 0, Pose::degToRad(0))
	// });

	// chassis.moveToPose(Pose(-24, 36, 0));
	// autoBuilder.followPath(testTrajectory, true);
	// autoBuilder.reset();
	// pros::delay(500);
	// autobuilder.reset();
	// autobuilder.followPath(testBackwardsTrajectory, false);

	// chassis.driveToY(35);
	// pros::delay(200);
	chassis.turnThenMoveToPose(Pose(0, 34, 0));
	pros::delay(200);
	std::cout << chassis.getPose().to_string() << std::endl;

	chassis.turnThenMoveToPose(Pose(7, 32, 0));
	pros::delay(200);

	std::cout << chassis.getPose().to_string() << std::endl;
	chassis.turnThenMoveToPose(Pose(-5, 32, 0), false);
	pros::delay(200);

	std::cout << chassis.getPose().to_string() << std::endl;

	std::cout << chassis.getPose().to_string() << std::endl;
	chassis.turnThenMoveToPose(Pose(-15, 37, 0));
	pros::delay(200);

	// chassis.turnAngle(315);

	// chassis.turnThenMoveToPose(Pose(3, 2, 0));
	// pros::delay(200);



	// chassis.turnAngle(-90);
	// pros::delay(20);
	// chassis.turnAngle(180);
	// pros::delay(20);																						
	// chassis.turnAngle(-140);
	// pros::delay(20);
	// chassis.turnAngle(20);

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
	controller.clear();
	while (true) {
		double leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		double rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		Pose pose = chassis.getPose();

		chassis.arcade(leftY, rightX);

		controller.print(0, 0, "%.2f %.2f %.2f", pose.getX(), pose.getY(), Pose::radToDeg(pose.getTheta()));
		controller.print(1, 0, "Y: %.2f X: %.2f", verticalTrackingWheel.getDistance(), horizontalTrackingWheel.getDistance());

		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
			autonomous();
		}

		// if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
		// 	intakeMotors.move(-100);
		// 	ejectorMotor.move(-100);
		// } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		// 	intakeMotors.move(100);
		// 	ejectorMotor.move(0);
		// } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		// 	intakeMotors.move(100);
		// 	ejectorMotor.move(100);
		// } else {
		// 	intakeMotors.move(0);
		// 	ejectorMotor.move(0);
		// }

		// if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
		// 	hood.extend();
		// } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
		// 	hood.retract();
		// }



		pros::delay(20);
	}
}