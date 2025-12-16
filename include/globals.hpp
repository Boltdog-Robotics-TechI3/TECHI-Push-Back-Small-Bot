#pragma once
// Libraries
#include "api.h"
#include "lib/api.hpp"

// Bot measurements
inline double wheel_diameter = 3.25;
inline double track_width = 10.75;
inline double gear_ratio = 3.0/4.0;

// Controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Motor Groups
inline pros::MotorGroup rightMotors({16, -18, 17});
inline pros::MotorGroup leftMotors({-14, 15, -13});
inline pros::MotorGroup intakeMotors({-12 ,19,-20});
inline pros::Motor top_Intake(12); 
inline pros::Motor low_intakeR(19);
inline pros::Motor low_intakeL(20);

inline pros::adi::Pneumatics hood('h',false);
inline pros::adi::Pneumatics scooper('g',false);
// Drivetrain
inline DifferentialDrivetrain drivetrain(&leftMotors, &rightMotors, wheel_diameter, track_width, gear_ratio);


// Tracking Wheel
inline pros::IMU imu(11);
inline TrackingWheel horizontalTrackingWheel(-2, 2.08, 0, WheelPosition::BACK);
inline TrackingWheel verticalTrackingWheel(-1, 2.08, 0.25, WheelPosition::LEFT);

// Odometry
inline Odometry odometry(&verticalTrackingWheel, NULL, &horizontalTrackingWheel, &imu);

// Chassis
inline DifferentialChassis chassis(&drivetrain, &odometry);
