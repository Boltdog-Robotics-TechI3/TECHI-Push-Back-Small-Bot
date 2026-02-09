#include "subsystems/intake.hpp"

void intakeInitialize()
{

    intakeMotors.set_brake_mode(pros::MotorBrake::coast);
}

void intakePeriodic()
{
    // if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    // {
    //     top_Intake.move(50);
    // }
    // else
    // {
    //     top_Intake.move(0);
    // }
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
    {
        bottomIntakeMotors.move(-127);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
    {
        intakeMotors.move(-127);
        bottomIntakeMotors.move(-127);
    }
    else if  (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
    intakeMotors.move(127);
    bottomIntakeMotors.move(127);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    bottomIntakeMotors.move(127);
    }
    else {
        intakeMotors.move(0);
        bottomIntakeMotors.move(0);
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
        hood.toggle();
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
        //odomRetract.toggle();

    }
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
        deScore.toggle();
    }
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
        MatchLoader.toggle();
    }
}