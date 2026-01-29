#include "main.h"
// brandon forge sucks at programming 
void intakeInitialize() {
    intakeMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    selectorMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    scoringMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    indexerMotor.set_brake_mode(MOTOR_BRAKE_COAST);
}

void intakePeriodic() {
	if (controller.get_digital(DIGITAL_L1)) { // Intaking
        hoodPiston.retract();
        liftPiston.extend();
        setIntakeSpeed(127);
        setLiftSpeed(65);
        setSelectorSpeed(127);
        setIndexerSpeed(127);
		
    } 
    else if (controller.get_digital(DIGITAL_L2)) { // Eject blocks
        hoodPiston.retract();
        liftPiston.extend();
        setIntakeSpeed(-100);
        setLiftSpeed(-65);
        setSelectorSpeed(-65);
        setIndexerSpeed(-65);
    } 
    else if (controller.get_digital(DIGITAL_R2)) { // Scoring High
        hoodPiston.extend();
        liftPiston.retract();
        setIntakeSpeed(127);
        setLiftSpeed(127);
        setSelectorSpeed(127);
        setIndexerSpeed(127);
    } 
    else if (controller.get_digital(DIGITAL_R1)) { // Scoring Mid
        hoodPiston.extend();
        liftPiston.extend();
        setIntakeSpeed(127);
        setLiftSpeed(127);
        setSelectorSpeed(127);
        setIndexerSpeed(127);
    } 
    else { // Idle
        setIntakeSpeed(0);
        setLiftSpeed(0);
        setSelectorSpeed(0);
        setIndexerSpeed(0);
    }
    
    if(controller.get_digital(DIGITAL_UP)){
        liftPiston.retract();
    }
    else if (controller.get_digital(DIGITAL_DOWN)){
        liftPiston.extend();
    }

    if(controller.get_digital(DIGITAL_B)){
        loaderPiston.retract();
    }
    else if (controller.get_digital(DIGITAL_X)){
        loaderPiston.extend();
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
