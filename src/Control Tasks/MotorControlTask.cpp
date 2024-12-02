#include "MotorControlTask.hpp"
#include "constants.hpp"
#include "sfr.hpp"

#include <Arduino.h>

void MotorControlTask::begin() {
    esc.attach(PWM_PIN, 1000, 2000);
    esc.write(0);
}

void MotorControlTask::execute() {
    if (sfr::flight::initial_hold && (millis() > constants::flight::initial_hold_time)) {
        sfr::flight::initial_hold = false;
        sfr::flight::initial_spin = true;
        esc.write(map(1180, 1000, 2000, 0, 180));
    }

    if (sfr::flight::initial_spin && (millis() > constants::flight::initial_spin_time)) {
        sfr::flight::initial_spin = false;
        set_white();
    }

    if (sfr::motor::spinning_up) {
        spinup();
    }
    if (sfr::motor::spin_down) {
        esc.write(0);

        sfr::motor::pulse_width_angle = 100;
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