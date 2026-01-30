#pragma once

#include "main.h"

// Initializes the intake system motors, setting brake mode
void intakeInitialize();

// Polls the controller and determines motor state
void intakePeriodic();

// Sets the speed of the intake motor to the specified parameter
void setIntakeSpeed(int speed);

// Sets the speed of the lift motor to the specified parameter
void setLiftSpeed(int speed);

// Sets the speed of the selector motor to the specified parameter
void setSelectorSpeed(int speed);

// Sets the speed of the indexer motor to the specified parameter
void setIndexerSpeed(int speed);

void startIntake();

void moveBallPath(int intakeSpeed, int liftSpeed, int selectorSpeed, int indexerSpeed);

void stopScoreHigh();

void startDejam();
