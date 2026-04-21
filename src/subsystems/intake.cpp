#include "subsystems/intake.hpp"
#include "globals.hpp"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"

#include <atomic>
#include <string>

namespace {
    bool leverReset = false; // Flag to determine if the lever is resetting
    std::atomic<bool> leverTimeoutReached{true}; // Flag to determine if the lever has fired and reset
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

Timer *leverTimer = nullptr;

void intakeInitialize()
{
    intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    lever.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

/**
 * Fire and reset the lever. Even with async enabled, this function does NOT run in a task. It simply returns after one pass
 * of the loop, so that it works nicely with control loops for opcontrol. Custom logic in the control loop 
 * is required to make it work with async on. Leave async off for most situations in autonomous.
 *
 * @param async Whether the function should run asynchronously or not.
 */
void fire(bool async=false) {
    if (leverTimer == nullptr) {
        leverTimer = new Timer(1000, onLeverTimeout); // Timer to determine if lever is stopped
    }

    if (!async) {
        leverTimeoutReached = false;
    }

    while (leverTimeoutReached == false) {
        if (leverReset) {
            lever.move(-127);
        } else {
            lever.move(127);
        }
        
        bool leverStopped = std::abs(lever.get_actual_velocity()*1.5) < abs(lever.get_target_velocity());
        if (leverStopped) {
            if (!leverTimer->isRunning()) {
                leverTimer->start();
            }
        } else {
            leverTimer->stop();
        }

        // Inner loops don't work well with control loops, return to caller and let the control loop handle the logic
        if (async) { return; }
        pros::delay(20);
    }
}

void countBlocks() {
    // Tasks start upon creation. This loops forces it to wait until its needed.
    // while (pros::Task::current().notify_take(true, TIMEOUT_MAX)) { pros::delay(20); };
    Timer blockTimer(100, []{});
    bool intaking;
    while (true) {
        if (counting) {
            double intakeVelocity = intake.get_actual_velocity();
            if (intakeVelocity < 150 && intaking) {
                blockTimer.start();
            } else if (blockTimer.isRunning() && intakeVelocity >= 200) {
                blockCount++;
                blockTimer.stop();
            } else {
                intaking = intakeVelocity >= 150;
            }
        } else {
            blockCount = 0;
            pros::Task::current().suspend(); // Task will suspend itself, so it resumes from a consistent location
            counting = true; // Task resumes from here, start counting
            intaking = false;
        }
        pros::delay(20);
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

    // Lever
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2) || leverTimeoutReached == false) {
        hood.extend();
        leverTimeoutReached = false;
        fire(false);
    }







    
    
}