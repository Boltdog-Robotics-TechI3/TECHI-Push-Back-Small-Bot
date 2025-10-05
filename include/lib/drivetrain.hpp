#pragma once

#include "pros/motor_group.hpp"

class Drivetrain {
    private:
        pros::MotorGroup *leftMotors;
        pros::MotorGroup *rightMotors;
        double wheelDiameter;
        double wheelTrackWidth;
        double gearRatio;
        friend class Chassis;
    public:
        Drivetrain(pros::MotorGroup *leftMotors, pros::MotorGroup *rightMotors, double wheelDiameter, double wheelTrackWidth, double gearRatio)
        : leftMotors(leftMotors), rightMotors(rightMotors), wheelDiameter(wheelDiameter), wheelTrackWidth(wheelTrackWidth), gearRatio(gearRatio) {}

        Drivetrain() : leftMotors(nullptr), rightMotors(nullptr), wheelDiameter(0), wheelTrackWidth(0) {}

        /**
         * @brief Get the wheel diameter.
         * @return The wheel diameter in inches.
         */
        double getWheelDiameter() const { return wheelDiameter; }

        /**
         * @brief Set the wheel diameter.
         * @param diameter The new wheel diameter in inches.
         */
        void setWheelDiameter(double diameter) { wheelDiameter = diameter; }

        /**
         * @brief Get the wheel track width (distance between left and right wheels).
         * @return The wheel track width in inches.
         */
        double getWheelTrackWidth() const { return wheelTrackWidth; }
        /**
         * @brief Set the wheel track width (distance between left and right wheels).
         * @param width The new wheel track width in inches.
         */
        void setWheelTrackWidth(double width) { wheelTrackWidth = width; }

        /**
         * @brief Get the gear ratio (output (wheel) speed / input (motor) speed).
         * @return The gear ratio.
         */
        double getGearRatio() const { return gearRatio; }
        /**
         * @brief Set the gear ratio (output (wheel) speed / input (motor) speed).
         * @param ratio The new gear ratio.
         */
        void setGearRatio(double ratio) { gearRatio = ratio; }
};