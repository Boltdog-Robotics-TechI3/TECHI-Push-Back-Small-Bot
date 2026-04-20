#pragma once
// Libraries
#include "lib/api.hpp"

// Bot measurements
inline double wheel_diameter = 3.25;
inline double track_width = 11.0;
inline double gear_ratio = 3.0/4.0;

// Controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Motor Groups
inline pros::MotorGroup rightMotors({-10, -19, 18, 17});
inline pros::MotorGroup leftMotors({-13, 14, -15, 16});
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
inline TrackingWheel horizontalTrackingWheel(1, 2.08, 1.25, WheelPosition::HORIZONTAL);
inline TrackingWheel verticalTrackingWheel(-2, 2.08, 0, WheelPosition::VERTICAL);

// Odometry
inline OdomSensors odometry(&verticalTrackingWheel,&horizontalTrackingWheel , &imu);
inline PIDController lateral(5,0,0);
inline PIDController turn(70,0,10.0);
inline PIDController align(50,0,0);
// Chassis
inline TankChassis chassis(&drivetrain, &odometry,&lateral,&turn,&align);


