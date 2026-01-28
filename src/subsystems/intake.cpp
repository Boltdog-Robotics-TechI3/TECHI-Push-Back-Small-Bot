#include "main.h"
bool loadOrLowForwards = true;
bool lowOrHighForwards = true;

void intakeInitialize() {
    intake1.set_brake_mode(MOTOR_BRAKE_COAST);
    intake2.set_brake_mode(MOTOR_BRAKE_COAST);
}

void intakePeriodic() {
	if (controller.get_digital(DIGITAL_L1)){ // intake
        hopper.move(0);
        lowOrHigh.move(0);
        setIntakeSpeed(127);
        hopper.move(0);
        lowOrHigh.move(0);
                

    }
    else if (controller.get_digital(DIGITAL_R1)){
        setIntakeSpeed(127);
    }
    

    /*if (controller.get_digital(DIGITAL_R1)){ // score high
        setIntakeSpeed(127);
        

    }*/

    else if (controller.get_digital(DIGITAL_L2)){ // outtake
        setIntakeSpeed(-127);
    }

    else if (controller.get_digital(DIGITAL_LEFT)){
        toggleLoadOrLow();
    }

    else if (controller.get_digital(DIGITAL_RIGHT)){
        togglelowOrHigh();
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
    hopper.move(speed);

    if (loadOrLowForwards) {
        loadOrLow.move(speed);
    }
    else { 
        loadOrLow.move(-speed);
    }

    if (lowOrHighForwards) {
        lowOrHigh.move(speed);
    }
    else { 
        lowOrHigh.move(-speed);
    }
}

void toggleLoadOrLow(){
    //if (controller.get_digital(DIGITAL_LEFT))
    if (loadOrLowForwards){setloadOrLowForwards(false);}
    else {setloadOrLowForwards(true);}
    //controller.clear();
    //controller.print(0,0, "port 8 : %b", getloadOrLowForwards());
    //pros::delay(100);
    
}

void togglelowOrHigh(){
    //if (controller.get_digital(DIGITAL_RIGHT))
    if (lowOrHighForwards){setlowOrHighForwards(false);}
    else {setlowOrHighForwards(true);}
    //controller.clear();
    //controller.print(0,0, "port 3 : %b", getlowOrHigh());
    //pros::delay(100);
    
}

bool getloadOrLowForwards(){
    return loadOrLowForwards;
}
void setloadOrLowForwards(bool stuff){
    loadOrLowForwards = stuff;
}

bool getlowOrHigh(){
    return lowOrHighForwards;
}

void setlowOrHighForwards(bool stuff){
    lowOrHighForwards = stuff;
}