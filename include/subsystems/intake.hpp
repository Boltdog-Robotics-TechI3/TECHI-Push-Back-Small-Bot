#pragma once

#include "main.h"


// Initializes the intake system motors, setting brake mode
void intakeInitialize();

// Polls the controller and determines intake motor state and match load piston state
void intakePeriodic();

// Polls the controller and determines lever motor, lift pistion, and wing piston states
void leverPeriodic();

void setLeverPosition(int position, int maxVel, int maxAccel);

// Sets the speed of the intake motor to the specified parameter
void setIntakeSpeed(int speed);

// Sets the speed of the lift motor to the specified parameter
void setLeverSpeed(int speed);
