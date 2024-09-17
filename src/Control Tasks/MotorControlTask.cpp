#include "MotorControlTask.hpp"
#include "sfr.hpp"
#include "constants.hpp"

#include <Arduino.h>


MotorControlTask::MotorControlTask() {
    esc.attach(PWM_PIN, 1000, 2000);
    esc.write(0);
}


void MotorControlTask::execute() {
    if (sfr::motor::spinning_up) {
        spinup();
    }
}

void MotorControlTask::spinup() {
    if (millis() - last_write > constants::motor::spinup_increment) {
        int val = map(sfr::motor::pulse_width, 0, 1000, 0, 200);
        esc.write(val);
        sfr::motor::pulse_width++;
        last_write = millis();
    }
    
    if (sfr::motor::pulse_width == 1000) {
        sfr::motor::spinning_up = false;
    }
}