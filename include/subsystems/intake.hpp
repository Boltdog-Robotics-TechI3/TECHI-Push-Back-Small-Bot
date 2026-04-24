#pragma once
#include "globals.hpp"
#include "api.h"

void intakeInitialize();
void intakePeriodic();
void fire();

void startCounting();
void suspendCounting();
inline std::atomic<bool> counting = false;
inline std::atomic<int> blockCount{0};

inline bool firing = false;
