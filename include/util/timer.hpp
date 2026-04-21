#pragma once
#include "api.h"
#include "pros/rtos.hpp"

typedef void (*callback_function)();

class Timer {
    private:
        callback_function callback;
        int time = 0; // in milliseconds
        int startTime = 0;
        bool initialized = false;
        std::atomic<bool> running = false;
        pros::Task task = pros::Task([this]() {
            while (true) {
                task.suspend();
                startTime = pros::millis();
                pros::lcd::print(0, "Timer Resumed %d", pros::millis());
                while (running && pros::millis() - startTime < time) { pros::delay(20); }
                if (running && callback) {
                    running = false;
                    callback();
                }
            }
        });
    public:
        Timer(int time, callback_function cb);
        ~Timer();
        void start();
        void stop();
        bool isRunning() { return running; }
        void setTime(int t) { time = t; }
        int getTime() { return time; }
};