#include "main.h"

void intakeInitialize() {
    intakeMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    leverMotor.set_brake_mode(MOTOR_BRAKE_COAST);
    leverMotor.set_gearing(pros::E_MOTOR_GEAR_RED);

}

void setIntakeSpeed(int speed) {
    intakeMotor.move(speed);
}

void setLeverSpeed(int speed) {
    leverMotor.move(speed);
}

bool isScoring = false;

void leverRetract() {
    isScoring = false;
    leverMotor.move(-100);
    pros::delay(100);
    leverMotor.move(0);
    
}

bool liftUp = false;
void leverScoreHigh(bool liftState) {
    if(liftState){
        isScoring = true;
        setIntakeSpeed(100);
        pros::delay(100);
        leverMotor.move_relative(650, 600);
    }
}

void leverScoreMid(int speed) {
    isScoring = true;
    setIntakeSpeed(100);
    pros::delay(100);
    leverMotor.move_relative(650, speed);
}



void intakePeriodic() {
//INTAKE CONTROLS
    if(!isScoring) {
        if (controller.get_digital(DIGITAL_L1)) { // Intaking
            setIntakeSpeed(127);
        } else if (controller.get_digital(DIGITAL_L2)) { // Eject blocks
            setIntakeSpeed(-100);
        }  else { // Idle
            setIntakeSpeed(30);
        }

        // MATCH LOAD PISTON
        if (controller.get_digital_new_press(DIGITAL_LEFT)) {
            matchLoadPiston.toggle();
        } 
    }
}

void leverPeriodic() {
//SCORING CONTROLS
    if (controller.get_digital_new_press(DIGITAL_R2)) { // Lever Score
        leverScoreHigh(liftUp);
    } if (controller.get_digital_new_release(DIGITAL_R2)) { // Lever DOWN
        if(liftUp){
            leverRetract(); 
        } else {
            liftPiston.extend();
            liftUp = true;
        } 
    }
    if (controller.get_digital_new_press(DIGITAL_R1)) { // Lever Score
        leverScoreMid(600);
    } if (controller.get_digital_new_release(DIGITAL_R1)) { // Lever DOWN
        leverRetract();  
    }
    if (controller.get_digital_new_press(DIGITAL_Y)) { // Lever Score
        leverScoreMid(75);
    } if (controller.get_digital_new_release(DIGITAL_Y)) { // Lever DOWN
        leverRetract();  
    }
//LEVER MANUAL OVERRIDE
    if (controller.get_digital(DIGITAL_X)) {
        setLeverSpeed(75);
    } else if (controller.get_digital(DIGITAL_B)) {
        setLeverSpeed(-75);
    } 
    if (controller.get_digital_new_release(DIGITAL_X) || controller.get_digital_new_release(DIGITAL_B)) {
        setLeverSpeed(0);
    }
    
//PNEUMATIC CONTROLS
    //LIFT PISTON
    if (controller.get_digital_new_press(DIGITAL_UP)) {
        liftPiston.extend();
        liftUp = true;
    }
    if (controller.get_digital_new_press(DIGITAL_DOWN)) {
        liftPiston.retract();
        wingPiston.retract();
    }
     
    // WING PISTON
    if (controller.get_digital_new_press(DIGITAL_A)) {
        wingPiston.toggle();
    }  
}
