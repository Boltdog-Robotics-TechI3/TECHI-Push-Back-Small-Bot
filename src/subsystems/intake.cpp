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
        bottomIntakemotors.move(-127);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
    {
        intakeMotors.move(-127);
    }
    else if  (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
    intakeMotors.move(127);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    bottomIntakemotors.move(127);
    }
    else {
        intakeMotors.move(0);
        bottomIntakemotors.move(0);
    }
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
        hood.extend();
    }else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
        hood.retract();

    }

}