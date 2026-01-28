#include "main.h"
// brandon forge sucks at programming 
void intakeInitialize() {
    intakeMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    selectorMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    scoringMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    indexerMotor.set_brake_mode(MOTOR_BRAKE_COAST);
}

void intakePeriodic() {
	if (controller.get_digital(DIGITAL_R1)) { // Intaking
        setIntakeSpeed(127);
        setLiftSpeed(65);
        setSelectorSpeed(127);
        setIndexerSpeed(127);
		
    } 
    else if (controller.get_digital(DIGITAL_R2)) { // Eject blocks
        setIntakeSpeed(-100);
        setLiftSpeed(-65);
        setSelectorSpeed(-65);
        setIndexerSpeed(-65);
    } 
    else if (controller.get_digital(DIGITAL_L2)) { // Scoring
        setIntakeSpeed(127);
        setLiftSpeed(127);
        setSelectorSpeed(127);
        setIndexerSpeed(127);
    } 
    else if (controller.get_digital(DIGITAL_L1)) { // Scoring mid intake side
        setIntakeSpeed(127);
        setLiftSpeed(-127);
        setSelectorSpeed(-127);
        setIndexerSpeed(-127);
    } 
    else { // Idle
        setIntakeSpeed(0);
        setLiftSpeed(0);
        setSelectorSpeed(0);
        setIndexerSpeed(0);
    }
    
    if(controller.get_digital(DIGITAL_UP)){
        setLiftPos(false);
    }
    else if (controller.get_digital(DIGITAL_DOWN)){
        setLiftPos(true);
    }

    if(controller.get_digital(DIGITAL_B)){
        setLoaderPos(false);
    }
    else if (controller.get_digital(DIGITAL_X)){
        setLoaderPos(true);
    }
}

void setIntakeSpeed(int speed) {
    intakeMotor.move(speed);
}

void setSelectorSpeed(int speed) {
    selectorMotor.move(speed);
}

void setLiftSpeed(int speed) {
    scoringMotor.move(speed);
}

void setIndexerSpeed(int speed) {
    indexerMotor.move(speed);
}

void setHoodPos(bool upward) {
    hoodPiston.set_value(upward);
}

void setLiftPos(bool upward) {
    liftPiston.set_value(upward);
}

void setLoaderPos(bool upward) {
    loaderPiston.set_value(upward);
}