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
    leverMotor.move(-127);
    pros::delay(150);
    leverMotor.move(-15);
    
}

bool liftUp = false;
void leverScoreHigh(bool liftState) {
    if(liftState){
        isScoring = true;
        setIntakeSpeed(100);
        pros::delay(100);
        leverMotor.move_relative(650, 450);
    }
}

void leverScoreMid(int speed, bool liftState) {
    if(!liftState){
        isScoring = true;
        setIntakeSpeed(100);
        pros::delay(100);
        leverMotor.move_relative(650, speed);
    }
}


void intakePeriodic() {
//INTAKE CONTROLS
    if(!isScoring) {
        if (controller.get_digital(DIGITAL_L1)) { // Intaking
            setIntakeSpeed(127);
            intakeForward = true;
        } else if (controller.get_digital(DIGITAL_A)) { // Eject blocks
            setIntakeSpeed(-100);
        }  else { // Idle
            setIntakeSpeed(30);
            intakeForward = false;
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
        leverScoreMid(600, liftUp);
    } if (controller.get_digital_new_release(DIGITAL_R1)) { // Lever DOWN
         if(!liftUp){
            leverRetract(); 
        } else {
            liftPiston.retract();
            liftUp = false;
        }  
    }
    if (controller.get_digital_new_press(DIGITAL_Y)) { // Lever Score
        leverScoreMid(200, false);
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
        setLeverSpeed(-15);
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
        liftUp = false;
    }
     
    // WING PISTON
    if (controller.get_digital_new_press(DIGITAL_L2)) {
        wingPiston.extend();
    }
    if (controller.get_digital_new_release(DIGITAL_L2)) {
        wingPiston.retract();
    }

}
