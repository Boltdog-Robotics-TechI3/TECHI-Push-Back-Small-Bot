#include "main.h"


inline const double wheelDiameter = 2.75;
inline const double trackWidth = 12.5;
inline const double gearRatio = 36.0 / 48.0;

// Drivetrain Pieces
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);
inline pros::MotorGroup leftDrive({3, -20, -19, 18});
inline pros::MotorGroup rightDrive({-4, 11, 12, -13});

inline TankDrivetrain drivetrain(&leftDrive, &rightDrive, wheelDiameter, trackWidth, gearRatio);

// Intake Pieces
inline pros::Motor intakeMotor(-1);
inline pros::Motor leverMotor(-15, pros::v5::MotorGears::red, pros::v5::MotorUnits::degrees);

inline PIDController leverPID(300, 0, 0);

inline pros::adi::Pneumatics liftPiston('F', false);
inline pros::adi::Pneumatics matchLoadPiston('G', false);
inline pros::adi::Pneumatics hoodPiston('H', false);

// Odometry Pieces
inline TrackingWheel verticalTrackingWheel(16, 2.08, 3.5, WheelPosition::VERTICAL);
inline TrackingWheel horizontalTrackingWheel(17, 2.08, 5.5, WheelPosition::HORIZONTAL);

inline pros::IMU imu(14);

inline OdomSensors odometry(&verticalTrackingWheel, &horizontalTrackingWheel, &imu);

inline PIDController lateral(3.75, 0.001, 0);
inline PIDController turn(60, 0.02, 0);
inline PIDController align(80, 0, 0);

inline TankChassis chassis(&drivetrain, &odometry ,&lateral, &turn, &align);

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
	chassis.setPose(0,0,0);
	// chassis.moveToPose({.targetPose={30, 30, 0}, .timeout=50000, .smallErrorTimeout=5000, .largeErrorTimeout=5000, .maxMoveSpeed=100, .maxMoveAccel=100, .smallMoveErrorRange=.5, .largeMoveErrorRange=.5, .minAlignDistance=1});
	chassis.turnToAngle({.targetAngle=90});
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

	chassis.startTracking();

	while (true) {
		leftY = controller.get_analog(ANALOG_LEFT_Y);
		rightX = controller.get_analog(ANALOG_RIGHT_X) * (1.0/2.0);
		
		chassis.arcade(leftY, rightX);

		controller.set_text(0, 0, chassis.getPose().to_string());

		if(controller.get_digital_new_press(DIGITAL_RIGHT)){
			autonomous();
		}
		pros::delay(20);
	}
}