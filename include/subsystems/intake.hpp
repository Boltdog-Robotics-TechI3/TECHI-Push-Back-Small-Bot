#pragma once
#include "globals.hpp"
#include "api.h"

void intakeInitialize();
void intakePeriodic();
void fire(bool async, int speed=127);

void startCounting();
void suspendCounting();
inline std::atomic<bool> counting = false;
inline std::atomic<int> blockCount{0};
