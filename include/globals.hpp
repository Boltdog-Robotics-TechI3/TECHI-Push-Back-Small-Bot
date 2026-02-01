#pragma once
#include "api.h"

inline bool skills = false;
inline bool match = true;
inline bool redAlliance = false;
inline bool blueAlliance = true;
inline int autoSelection = 0;

inline const double wheelDiameter = 2.75;
inline const double trackWidth = 12.5;
inline const double gearRatio = 36.0 / 48.0;

// Drivetrain Pieces
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);
inline pros::MotorGroup leftDrive({18, -19, -20});
inline pros::MotorGroup rightDrive({11, 12, -13});

inline DifferentialDrivetrain drivetrain(&leftDrive, &rightDrive, wheelDiameter, trackWidth, gearRatio);

// Intake Pieces
inline pros::Motor intakeMotor(-6);
inline pros::Motor scoringMotor(8);
inline pros::Motor indexerMotor(-9);
inline pros::Motor selectorMotor(10);

inline pros::adi::Pneumatics liftPiston('A', false);
inline pros::adi::Pneumatics hoodPiston('E', false);
inline pros::adi::Pneumatics loaderPiston('C', false);

// Odometry Pieces
inline TrackingWheel verticalTrackingWheel(-16, 2.08, 1.875, WheelPosition::LEFT);
inline TrackingWheel horizontalTrackingWheel(-17, 2.08, -1, WheelPosition::BACK);

inline pros::IMU imu(15);

inline Odometry odometry(&verticalTrackingWheel, NULL, &horizontalTrackingWheel, &imu);

inline PIDController Lateral(8,0,.1);
inline PIDController Turn(60,0.2,0);
inline PIDController Align(30,0,0);

inline DifferentialChassis chassis(&drivetrain, &odometry ,&Lateral, &Turn, &Align);