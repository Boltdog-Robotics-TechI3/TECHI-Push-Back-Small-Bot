#include "main.h"

void setWing(bool stuff){
    if (stuff){
        wing.extend();
    }
    else {
        wing.retract();
    }
    
}

void wingPeriodic(){
    if (controller.get_digital(DIGITAL_A)){
        setWing(true);
    }   

    if (controller.get_digital(DIGITAL_B)){
        setWing(false);
    }
}