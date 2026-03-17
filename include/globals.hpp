#pragma once
#include "api.h"

inline bool skills = false;
inline bool match = true;
inline bool redAlliance = false;
inline bool blueAlliance = true;
inline int autoSelection = 0;

inline bool intakeForward = false;


inline const double wheelDiameter = 2.75;
inline const double trackWidth = 12.5;
inline const double gearRatio = 36.0 / 48.0;

// Drivetrain Pieces
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);
inline pros::MotorGroup leftDrive({-11, -12, 13});
inline pros::MotorGroup rightDrive({-18, 19, 20});

inline TankDrivetrain drivetrain(&leftDrive, &rightDrive, wheelDiameter, trackWidth, gearRatio);

// Intake Pieces
inline pros::Motor intakeMotor(-1);
inline pros::Motor leverMotor(-15, pros::v5::MotorGears::red, pros::v5::MotorUnits::degrees);

inline PIDController leverPID(300, 0, 0);

inline pros::adi::Pneumatics liftPiston('F', false);
inline pros::adi::Pneumatics matchLoadPiston('G', false);
inline pros::adi::Pneumatics wingPiston('H', false);

// Odometry Pieces
inline TrackingWheel verticalTrackingWheel(-16, 2.08, -3.5, WheelPosition::VERTICAL);
inline TrackingWheel horizontalTrackingWheel(-17, 2.08, -5.5, WheelPosition::HORIZONTAL);

inline pros::IMU imu(14);

inline OdomSensors odometry(&verticalTrackingWheel, &horizontalTrackingWheel, &imu);

inline PIDController lateral(3.75, 0.001, 0);
inline PIDController turn(80, 0.2, 0);
inline PIDController align(80, 0, 0);

inline TankChassis chassis(&drivetrain, &odometry ,&lateral, &turn, &align);