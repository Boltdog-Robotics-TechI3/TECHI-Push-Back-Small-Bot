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
inline pros::MotorGroup leftMotors({10, 19, -18, -17});
inline pros::MotorGroup rightMotors({13, -14, 15, -16});
inline pros::Motor intake(20);
inline pros::Motor lever(12); 

inline pros::adi::Pneumatics lift('b', false);
inline pros::adi::Pneumatics hood('a', false);
inline pros::adi::Pneumatics matchLoader('h', false);

// Drivetrain
inline TankDrivetrain drivetrain(&leftMotors, &rightMotors, wheel_diameter, track_width, gear_ratio);

// Tracking Wheel
inline pros::IMU imu(11);
// TODO: Check tracking wheel offsets and diameters
inline TrackingWheel horizontalTrackingWheel(-1, 2.08, 3.5, WheelPosition::HORIZONTAL);
inline TrackingWheel verticalTrackingWheel(2, 2.08, -.5, WheelPosition::VERTICAL);

// Odometry
inline OdomSensors odometry(&verticalTrackingWheel,&horizontalTrackingWheel , &imu);
inline PIDController lateral(8,0,0);
inline PIDController turn(60,0.2,3);
inline PIDController align(60,0,0);
// Chassis
inline TankChassis chassis(&drivetrain, &odometry,&lateral,&turn,&align);


