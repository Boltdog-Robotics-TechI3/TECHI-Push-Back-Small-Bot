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
inline pros::MotorGroup rightMotors({7, -8, 9});
inline pros::MotorGroup leftMotors({-13, 14, -15});
inline pros::MotorGroup intakeMotors({5,-4,1});
inline pros::MotorGroup bottomIntakeMotors({5,-4});
inline pros::Motor top_Intake(1); 

inline pros::adi::Pneumatics hood('a',false);
inline pros::adi::Pneumatics deScore('c',false);
inline pros::adi::Pneumatics MatchLoader('d',false);
inline pros::adi::Pneumatics odomRetract('h',false);
// Drivetrain
inline DifferentialDrivetrain drivetrain(&leftMotors, &rightMotors, wheel_diameter, track_width, gear_ratio);


// Tracking Wheel
inline pros::IMU imu(6);
inline TrackingWheel horizontalTrackingWheel(-2, 2.08, -4.375, WheelPosition::BACK);
inline TrackingWheel verticalTrackingWheel(-10, 2.08, 0, WheelPosition::LEFT);

// Odometry
inline Odometry odometry(&verticalTrackingWheel, NULL,&horizontalTrackingWheel , &imu);
inline PIDController lateral(8,0,0);
inline PIDController turn(60,0.2,3);
inline PIDController align(30,0,0);
// Chassis
inline DifferentialChassis chassis(&drivetrain, &odometry,&lateral,&turn,&align);

