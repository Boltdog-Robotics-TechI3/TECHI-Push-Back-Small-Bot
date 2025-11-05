#pragma once
#include "api.h"

inline const double wheelDiameter = 2.75;
inline const double trackWidth = 12.5;
inline const double gearRatio = 36.0 / 48.0;

inline pros::Controller controller(pros::E_CONTROLLER_MASTER);
inline pros::MotorGroup leftDrive({-18, -19, 20});
inline pros::MotorGroup rightDrive({8, 9, -10});

inline pros::Motor intake(7);

inline DifferentialDrivetrain drivetrain(&leftDrive, &rightDrive, wheelDiameter, trackWidth, gearRatio);

inline TrackingWheel verticalTrackingWheel(7, 2, 0, WheelPosition::LEFT);
inline TrackingWheel horizontalTrackingWheel(6, 2, 0, WheelPosition::BACK);

inline pros::IMU gyro(5);

inline Odometry odometry(&verticalTrackingWheel, NULL, &horizontalTrackingWheel, &gyro);

inline DifferentialChassis chassis(&drivetrain, &odometry);