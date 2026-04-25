#include "subsystems/intake.hpp"
#include "globals.hpp"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"

#include <atomic>
#include <string>

namespace {
    std::atomic<bool> leverReset{false}; // Flag to determine if the lever is resetting
    std::atomic<bool> leverTimeoutReached{true}; // Flag to determine if the lever has fired and reset
    bool isMidScore = false;
    int leverSpeed = 127;
    void onLeverTimeout() {
        if (leverReset) {
            leverTimeoutReached = true;
            leverReset = false;
        } else {
            leverReset = true;
            hood.retract();
        }
        lever.brake(); 
    }
}

void intakeJamHandler(void* param) {
    int stallTime = -1;
    while (true) {
        if (intake.get_actual_velocity() == 0 && intake.get_target_velocity() > 0) {
            if (stallTime == -1) {
                stallTime = pros::millis();
            } else if (pros::millis() - stallTime >= 150) {
                intake.move(-127);
                pros::delay(100);
                intake.move(127);
            }
        } else {
            stallTime = -1;
        }
        pros::delay(20);
    }
}

pros::Task intakeJamTask(intakeJamHandler);

Timer *leverTimer = nullptr;

void intakeInitialize()
{
    intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    lever.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

bool resetting = false;

void fire() {
    firing = true;
}

void fire_lever(void* params) {
    while (true) {
        if (firing) {
            int deadline = pros::millis() + 500;
            int settledSince = -1;
            while (firing) {
                if (resetting) {
                    lever.move(-100);
                } else {
                    lever.move(leverSpeed);
                }

                bool settled = std::abs(lever.get_actual_velocity()*1.5) < abs(lever.get_target_velocity());

                if (settled) {
                    controller.set_text(0,0, std::to_string(resetting));
                    if (settledSince == -1) {
                        settledSince = pros::millis();
                    } else if (pros::millis() - settledSince > 500) {
                        if (!resetting) {
                            deadline = pros::millis() + 500;
                            settled = false;
                            resetting = true;
                            settledSince = -1;
                        } else {
                            resetting = false;
                            firing = false;
                            settledSince = -1;
                        }
                    }
                } else {
                    settledSince = -1;
                }
                pros::delay(20);
            }
        }
        lever.move(0);
        pros::delay(20);
    }
}

pros::Task fireTask(fire_lever);

void countBlocks() {
    // Tasks start upon creation. This loops forces it to wait until its needed.
    // while (pros::Task::current().notify_take(true, TIMEOUT_MAX)) { pros::delay(20); };
    Timer cooldownTimer(325, []{});
    Timer warmupTimer(200, []{});
    bool intaking = false;
    double previousVelocity = 0;
    while (true) {
        if (counting) {
            double intakeVelocity = intake.get_actual_velocity();
            if (intake.get_torque() > 0.5 && !cooldownTimer.isRunning() && !warmupTimer.isRunning()) {
                blockCount++;
                cooldownTimer.start();
            }
            if (previousVelocity*2 < intakeVelocity && !warmupTimer.isRunning()) {
                warmupTimer.start();
            }
            previousVelocity = intakeVelocity;
        } else {
            blockCount = 0;
            pros::Task::current().suspend(); // Task will suspend itself, so it resumes from a consistent location
            counting = true; // Task resumes from here, start counting
            intaking = false;
        }
    }

}
pros::Task countTask(countBlocks);

void startCounting() {
    countTask.resume();
}
void suspendCounting() {
    counting = false;
}
void intakePeriodic()
{
    // Intake
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        intake.move(-127);
    } else if  (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        intake.move(127);
    } else {
        intake.move(0);
    }

    // Lift
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
        lift.toggle();
    }

    // Match Load
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
        matchLoader.toggle();
    }

    // hood and wing
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
        hood.extend();
    } else{
        hood.retract();
    }

    // normal Lever
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
        isMidScore = false;
        leverSpeed = 127;
        hood.extend();
        leverTimeoutReached = false;
        fire();
    }

    // middle goal lever
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        isMidScore = true;
        leverSpeed = 80;
        hood.extend();
        leverTimeoutReached = false;
        fire();
    }
    
    
}