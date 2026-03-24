#include "main.h"
// minimum is 0, max is 70

std::atomic<bool> isLeverSettled = false;

float targetPosition = 0;
float maxVel = 0;
float maxAccel = 0;

pros::Task leverTask = pros::Task([]() {
    while(1) {
        isLeverSettled = false;

        Timer timeoutTimer(2000, +[]() { isLeverSettled = true; });
        Timer largeErrorTimer(500, +[]() { isLeverSettled = true; });
        
        int output;
        int startTime = pros::millis();

        leverPID.reset();

        leverPID.setOutputLimits(-maxVel, maxVel);
        leverPID.setLargeErrorRange(50);
        leverPID.setSlewRate(maxAccel);
        
        timeoutTimer.start();

        while (!isLeverSettled) {
            if (leverTask.notify_clear()) {
                isLeverSettled = true;
                break;
            }
            
            output = leverPID.calculate(leverMotor.get_position(), targetPosition);

            setLeverSpeed(output);

            if (leverMotor.get_actual_velocity() <= 5 && 1500 < (pros::millis() - startTime)){
                isLeverSettled = true;
            }

            if (leverPID.isInLargeErrorRange()) {
                largeErrorTimer.start();
            }
            else {
                largeErrorTimer.stop();
            }

            pros::delay(20);
        }

        largeErrorTimer.stop();
        timeoutTimer.stop();
        setLeverSpeed(0);
        
        pros::delay(20);
    }
});

void intakeInitialize() {
    intakeMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    leverMotor.set_brake_mode(MOTOR_BRAKE_COAST);
}

void setIntakeSpeed(int speed) {
    intakeMotor.move(speed);
}

void setLeverSpeed(int speed) {
    leverMotor.move(speed);
}

void intakePeriodic() {
    if (controller.get_digital(DIGITAL_L1)) {
        hoodPiston.retract();
        setIntakeSpeed(127);
    }
    else if (controller.get_digital(DIGITAL_A)) {
        setIntakeSpeed(-127);
    }
    else {
        setIntakeSpeed(30);
    }
    
}

void leverPeriodic() {
    if (controller.get_digital_new_press(DIGITAL_UP)) {
        liftPiston.extend();
    }
    else if (controller.get_digital_new_press(DIGITAL_DOWN)) {
        liftPiston.retract();
    }

    if (controller.get_digital_new_press(DIGITAL_R2)) {
        hoodPiston.extend();
        setIntakeSpeed(127);

        setLeverState(200, 127, 400);
    } 
    else if (controller.get_digital_new_press(DIGITAL_R1)){
        hoodPiston.extend();
        setIntakeSpeed(127);

        setLeverState(120,50, 400);
    }
    else if (isLeverSettled && targetPosition) {
        setLeverState(0, 50, 100);
    }

    // else if (controller.get_digital(DIGITAL_B)) {
    //     setLeverSpeed(-75);
    // } 
    // if (!controller.get_digital_new_press(DIGITAL_R2) && !controller.get_digital_new_press(DIGITAL_B) && !controller.get_digital_new_press(DIGITAL_R1)){
    //     setLeverSpeed(-15);
    // }
    // if (leverMotor.get_position() <= 0){
    //     setLeverSpeed(0);
    // }

    if (controller.get_digital_new_press(DIGITAL_L2)) {
        hoodPiston.extend();
    } 
    else if (controller.get_digital_new_release(DIGITAL_L2)) 
        hoodPiston.retract();
}

void setLeverState(float post, float vel, float accel){
    leverTask.suspend();
    targetPosition = post;
    maxVel = vel;
    maxAccel = accel;
    leverTask.notify();
    leverTask.resume();
}