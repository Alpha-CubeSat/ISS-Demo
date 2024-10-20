#include "MotorControlTask.hpp"
#include "constants.hpp"
#include "sfr.hpp"

#include <Arduino.h>

void MotorControlTask::begin() {
    esc.attach(PWM_PIN, 1000, 2000);
    esc.write(0);
}

void MotorControlTask::execute() {
    if (sfr::motor::spinning_up) {
        spinup();
    }
    if (sfr::motor::spin_down) {
        esc.write(0);

        sfr::motor::spin_down = false;
        sfr::motor::spinning_up = false;
    }
}

void MotorControlTask::spinup() {
    if (millis() - last_write > constants::motor::spinup_increment) {
        esc.write(sfr::motor::pulse_width_angle);
        sfr::motor::pulse_width_angle++;
        last_write = millis();
        vlogln(sfr::motor::pulse_width_angle);
    }

    if (sfr::motor::pulse_width_angle == 110) {
        sfr::motor::spinning_up = false;
    }
}