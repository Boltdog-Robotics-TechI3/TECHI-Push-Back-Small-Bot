#include "main.h"
#include <math.h>

float toRadians(float degrees) {
    return degrees * M_PI / 180.0;
}

void wiggle(int speed){
	for(int i = 0; i < 10; i++ ){
		leftDrive.move(speed);
		rightDrive.move(speed);
		pros::delay(100);
		leftDrive.move(0);
		rightDrive.move(0);
		pros::delay(100);
	}
    leftDrive.move(0);
    rightDrive.move(0);
}


void threeMidNineHigh() {

}

void doNothing(){
    wingPiston.extend();
}

void fourHigh(){

}