#pragma once

#include "main.h"


// Initializes the intake system motors, setting brake mode
void intakeInitialize();

// Polls the controller and determines intake motor state and match load piston state
void intakePeriodic();

// Polls the controller and determines lever motor, lift pistion, and wing piston states
void leverPeriodic();

void leverRetract();
void leverScoreHigh(bool liftState);
void leverScoreMid(int speed, bool liftState);

// Sets the speed of the intake motor to the specified parameter
void setIntakeSpeed(int speed);

// Sets the speed of the lift motor to the specified parameter
void setLeverSpeed(int speed);

// Sets the speed of the selector motor to the specified parameter
void setSelectorSpeed(int speed);

// Sets the speed of the indexer motor to the specified parameter
void setIndexerSpeed(int speed);

void startIntake();

void moveBallPath(int intakeSpeed, int liftSpeed, int selectorSpeed, int indexerSpeed);

void stopScoreHigh();

void startDejam();
