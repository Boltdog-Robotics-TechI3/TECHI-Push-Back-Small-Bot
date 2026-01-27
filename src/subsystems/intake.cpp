#include "main.h"
void intakeInitialize() {
    intake1.set_brake_mode(MOTOR_BRAKE_COAST);
    intake2.set_brake_mode(MOTOR_BRAKE_COAST);
}

void intakePeriodic() {
	if (controller.get_digital(DIGITAL_L1)){
        setIntakeSpeed(127);
    }

    else if (controller.get_digital(DIGITAL_L2)){
        setIntakeSpeed(-127);
    }

	else {
		setIntakeSpeed(0);
    }
}

void setIntakeSpeed(int speed){
    intake1.move(speed);
    intake2.move(speed);
    bottomRollers.move(speed);
    midRoller.move(speed);
    colorSorter.move(speed);
}