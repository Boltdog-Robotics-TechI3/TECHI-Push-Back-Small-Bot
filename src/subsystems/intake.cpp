#include "main.h"
// brandon forge sucks at programming 
void intakeInitialize() {
    intakeMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    selectorMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    liftMotor.set_brake_mode(MOTOR_BRAKE_COAST);
}

void intakePeriodic() {
	if (controller.get_digital(DIGITAL_L1)) { // Intaking
        setIntakeSpeed(127);
        setLiftSpeed(50);
        setSelectorSpeed(127);
        setHoodPos(false);
    }
	else if (controller.get_digital(DIGITAL_R1)) { // Scoring out hood
		setIntakeSpeed(127);
        setLiftSpeed(127);
        setSelectorSpeed(127);
        setHoodPos(true);
    } 
    else if (controller.get_digital(DIGITAL_L2)) { // Eject blocks
		setIntakeSpeed(-127);
        setLiftSpeed(-127);
        setSelectorSpeed(-127);
    } 
    else if (controller.get_digital(DIGITAL_R2)) { // Scoring out front
		setIntakeSpeed(127);
        setLiftSpeed(-127);
        setSelectorSpeed(-127);
    } 
    else { // Idle
        setIntakeSpeed(0);
        setLiftSpeed(0);
        setSelectorSpeed(0);
    }
    
    if(controller.get_digital(DIGITAL_UP)){
        setLiftPos(false);
    }
    else if (controller.get_digital(DIGITAL_DOWN)){
        setLiftPos(true);
    }
}

void setIntakeSpeed(int speed) {
    intakeMotor.move(speed);
}

void setSelectorSpeed(int speed) {
    selectorMotor.move(speed);
}

void setLiftSpeed(int speed) {
    liftMotor.move(speed);
}

void setHoodPos(bool upward) {
    hoodPiston.set_value(upward);
}

void setLiftPos(bool upward) {
    liftPiston.set_value(upward);
}