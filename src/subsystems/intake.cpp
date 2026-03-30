#include "main.h"

LeverState leverState = LeverState::IDLE;

std::atomic<bool> isLeverSettled = false;

int maxSpeed = 127;

pros::Task leverTask = pros::Task([]() {
    while(1) {
        switch (leverState) {
            case IDLE:
                setIntakeSpeed(20);
                break;
            case INTAKING:
                setIntakeSpeed(127);
                break;
            case OUTTAKING:
                setIntakeSpeed(-80);
                break;
            case SCORING:
                setIntakeSpeed(127);
                setLeverPosition(200, maxSpeed, 400);
                setIntakeSpeed(-30);
                setLeverPosition(0, 50, 100);
                setLeverState(LeverState::IDLE);
                break;
        }

        pros::delay(20);
    }
});

void leverInitialize() {
    intakeMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    leverMotor.set_brake_mode(MOTOR_BRAKE_COAST);
}

void setLeverState(LeverState state) {
    leverState = state;
}

void setIntakeSpeed(int speed) {
    intakeMotor.move(speed);
}

void setLeverSpeed(int speed) {
    leverMotor.move(speed);
}

void leverPeriodic() {
    if (controller.get_digital(DIGITAL_L1) && leverState != LeverState::SCORING) {
        hoodPiston.retract();
        setLeverState(LeverState::INTAKING);
    }
    else if (controller.get_digital(DIGITAL_A) && leverState != LeverState::SCORING) {
        hoodPiston.retract();
        setLeverState(LeverState::OUTTAKING);
    }    
    else if (controller.get_digital_new_press(DIGITAL_R2)) {
        if (hoodPiston.is_extended()) {
            maxSpeed = 127;
            setLeverState(LeverState::SCORING);
        }
        else {
            hoodPiston.extend();
        }
    } 
    else if (controller.get_digital_new_press(DIGITAL_R1)) {
        if (hoodPiston.is_extended()) {
            maxSpeed = 90;
            setLeverState(LeverState::SCORING);
        }
        else {
            hoodPiston.extend();
        }
    } 
    else if (controller.get_digital_new_press(DIGITAL_X)){
        if (hoodPiston.is_extended()) {
            maxSpeed = 50;
            setLeverState(LeverState::SCORING);
        }
        else {
            hoodPiston.extend();
        }
    }
    else if (leverState != LeverState::SCORING) {
        setLeverState(LeverState::IDLE);
    }

    if (controller.get_digital_new_press(DIGITAL_UP)) {
        liftPiston.extend();
    }
    else if (controller.get_digital_new_press(DIGITAL_DOWN)) {
        liftPiston.retract();
    }

    if (controller.get_digital_new_press(DIGITAL_L2)) {
        hoodPiston.retract();
    } 
    else if (controller.get_digital_new_release(DIGITAL_L2))  {
        hoodPiston.extend();
    }
}

void leverClosedLoop(float targetPosition, float maxVel, float maxAccel) {
    int output = leverPID.calculate(leverMotor.get_position(), targetPosition);
    setLeverSpeed(output);
}

void setLeverPosition(float targetPosition, float maxVel, float maxAccel) {
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
        leverClosedLoop(targetPosition, maxVel, maxAccel);

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
}
