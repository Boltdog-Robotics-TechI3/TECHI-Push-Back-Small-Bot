#include "main.h"

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
	if (controller.get_digital(DIGITAL_L1)) { // Intaking
        setIntakeSpeed(127);
		
    } 
    else if (controller.get_digital(DIGITAL_L2)) { // Eject blocks
        setIntakeSpeed(-70);
    } else { // Idle
        setIntakeSpeed(30);
    }


    if (controller.get_digital(DIGITAL_X)) { // Scoring High
        setLeverSpeed(60);  
    } else  if (controller.get_digital(DIGITAL_Y)) { // Scoring High
        setLeverSpeed(-50);  
    } else {
        setLeverSpeed(0);
    }
    
    

    if (controller.get_digital_new_press(DIGITAL_UP)) {
        liftPiston.extend();
    }
    
    if (controller.get_digital_new_press(DIGITAL_DOWN)) {
        liftPiston.retract();
    }
    if (controller.get_digital_new_press(DIGITAL_LEFT)) {
        matchLoadPiston.extend();
    }
    
    if (controller.get_digital_new_press(DIGITAL_RIGHT)) {
        matchLoadPiston.retract();
    }

    
}
