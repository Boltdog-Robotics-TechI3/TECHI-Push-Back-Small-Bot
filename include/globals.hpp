#pragma once
#include "main.h"

inline bool skills = false;
inline bool match = true;
inline bool redAlliance = false;
inline bool blueAlliance = true;
inline int autoSelection = 0;

inline const double wheelDiameter = 2.75;
inline const double trackWidth = 12.5;
inline const double gearRatio = 36.0 / 48.0;

inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

inline pros::MotorGroup frontLeftDrive({1, -2});
inline pros::MotorGroup frontRightDrive({9, -10});
inline pros::MotorGroup backLeftDrive({11, -12});
inline pros::MotorGroup backRightDrive({19, -20});


inline pros::Motor intake(7);

inline HolonomicDrivetrain drivetrain(&frontLeftDrive, &frontRightDrive, &backLeftDrive, &backRightDrive, wheelDiameter, trackWidth, gearRatio);

inline TrackingWheel verticalTrackingWheel(7, 2, 0, WheelPosition::LEFT);
inline TrackingWheel horizontalTrackingWheel(6, 2, 0, WheelPosition::BACK);

inline pros::IMU gyro(5);

inline Odometry odometry(&verticalTrackingWheel, NULL, &horizontalTrackingWheel, &gyro);

inline HolonomicChassis chassis(&drivetrain, &odometry);