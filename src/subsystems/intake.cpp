#include "main.h"

void intakeInitialize() {
    intakeMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    selectorMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    scoringMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    indexerMotor.set_brake_mode(MOTOR_BRAKE_COAST);

}

void intakePeriodic() {
	if (controller.get_digital(DIGITAL_L1)) { // Intaking
        setIntakeSpeed(127);
        setLiftSpeed(65);
        setSelectorSpeed(127);
        setIndexerSpeed(127);
		
    } 
    else if (controller.get_digital(DIGITAL_L2)) { // Eject blocks
        setIntakeSpeed(-100);
        setLiftSpeed(-65);
        setSelectorSpeed(-65);
        setIndexerSpeed(-65);
    } 
    else if (controller.get_digital(DIGITAL_R2)) { // Scoring High
        setIntakeSpeed(127);
        setLiftSpeed(127);
        setSelectorSpeed(127);
        setIndexerSpeed(127);
    } 
    else if (controller.get_digital(DIGITAL_R1)) { // Scoring Mid
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

    if (controller.get_digital_new_press(DIGITAL_L1) || controller.get_digital_new_press(DIGITAL_L2)) {
        hoodPiston.retract();
        // liftPiston.extend();
    }

    if (controller.get_digital_new_press(DIGITAL_R1)) {
        hoodPiston.extend();
        liftPiston.extend();
    }
    
    if (controller.get_digital_new_press(DIGITAL_R2)) {
        hoodPiston.extend();
        liftPiston.retract();
    }

    if(controller.get_digital_new_press(DIGITAL_UP)){
        liftPiston.retract();
    }

    else if (controller.get_digital_new_press(DIGITAL_DOWN)){
        liftPiston.extend();
    }

    if (controller.get_digital_new_press(DIGITAL_B)){
        if (loaderPiston.is_extended()) {
            loaderPiston.retract();
        }
        else {
            liftPiston.retract();
            loaderPiston.extend();
        }
  
    }

    if (loaderPiston.is_extended()) {
        liftPiston.extend();
    }

    
    // else if (controller.get_digital_new_press(DIGITAL_X)){
    //     loaderPiston.extend();
    // }
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


void moveBallPath(int intakeSpeed, int liftSpeed, int selectorSpeed, int indexerSpeed){
    setIntakeSpeed(intakeSpeed);
    setLiftSpeed(liftSpeed);
    setSelectorSpeed(selectorSpeed);
    setIndexerSpeed(indexerSpeed);
}
