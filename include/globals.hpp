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
// cant tell which way for 11 bc shaft is out
inline pros::MotorGroup rightMotors({11, 13, -14, 12});
// cant tell which way for 15 and 16 bc brain is broken
inline pros::MotorGroup leftMotors({15, 16, 1, -2});
//cant tell whic was bc brain again
inline pros::Motor intake(17);
inline pros::MotorGroup lever({-20, 10});

// have not done this yet
inline pros::adi::Pneumatics lift('b', false);
inline pros::adi::Pneumatics hood('a', false, true);
inline pros::adi::Pneumatics matchLoader('h', false);


// Drivetrain
inline TankDrivetrain drivetrain(&leftMotors, &rightMotors, wheel_diameter, track_width, gear_ratio);

// Tracking Wheel
// have not done this yet
inline pros::IMU imu(11);
// TODO: Check tracking wheel offsets and diameters
inline TrackingWheel horizontalTrackingWheel(1, 2.08, 1.25, WheelPosition::HORIZONTAL);
inline TrackingWheel verticalTrackingWheel(-2, 2.08, 0, WheelPosition::VERTICAL);

// Odometry
inline OdomSensors odometry(&verticalTrackingWheel,&horizontalTrackingWheel , &imu);
inline PIDController lateral(5,0,0);
inline PIDController turn(70,0,8.0);
inline PIDController align(50,0,0);
// Chassis
inline TankChassis chassis(&drivetrain, &odometry,&lateral,&turn,&align);


