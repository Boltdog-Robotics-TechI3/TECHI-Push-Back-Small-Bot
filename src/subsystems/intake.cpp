#include "subsystems/intake.hpp"
#include "globals.hpp"
#include "lib/pid.hpp"
#include "pros/abstract_motor.hpp"

#include <atomic>

namespace {
    bool leverReset = false;
    std::atomic<bool> leverTimeoutReached{true};
    void onLeverTimeout() {
        if (leverReset) {
            leverTimeoutReached = true;
            leverReset = false;
        } else {
            leverReset = true;
        }
        lever.brake(); 
    }
}

Timer *leverTimer = nullptr;

void intakeInitialize()
{
    intake.set_brake_mode(pros::MotorBrake::coast);
    lever.set_brake_mode(pros::MotorBrake::brake);
}

void resetLever() {

}

void fire() {
    if (leverTimer == nullptr) {
        leverTimer = new Timer(1000, onLeverTimeout);
    }

    if (leverTimeoutReached == false) {
        if (leverReset) {
            lever.move(-127);
        } else {
            lever.move(127);
        }
        
        bool leverStopped = abs(lever.get_actual_velocity()*1.5) < abs(lever.get_target_velocity());
        if (leverStopped) {
            if (!leverTimer->isRunning()) {
                leverTimer->start();
            }
        } else {
            leverTimer->stop();
        }
    }
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

    // Wing & Hood
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
        hood.retract();
    }

    if(controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_A)){
        hood.extend();
    }

    // Match Load
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
        matchLoader.toggle();
    }

    // Lever
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2) || leverTimeoutReached == false) {
        leverTimeoutReached = false;
        fire();
    }









    
    
}