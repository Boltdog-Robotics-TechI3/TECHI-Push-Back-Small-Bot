#pragma once
#include "api.h"
#include "pros/rtos.hpp"

typedef void (*callback_function)();

class Timer {
    private:
        callback_function callback;
        int time = 0; // in milliseconds
        bool initialized = false;
        std::atomic<bool> running = false;
        pros::Task task = pros::Task([this]() {
            while (true) {
                task.suspend();
                pros::delay(this->time);
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
};