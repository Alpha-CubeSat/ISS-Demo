#include "MotorControlTask.hpp"
#include "constants.hpp"
#include "sfr.hpp"

#include <Arduino.h>

void MotorControlTask::begin() {
   // vlogln("started motor control task");
    esc.attach(PWM_PIN, 1000, 2000);
    esc.write(0);
}

void MotorControlTask::execute() {
    if (sfr::flight::initial_hold && (millis() > constants::flight::initial_hold_time)) {
        sfr::flight::initial_hold = false;
        sfr::flight::initial_spin = true;
        esc.write(map(1300, 1000, 2000, 0, 180));
    }

    if (sfr::flight::initial_spin && (millis() > constants::flight::initial_spin_time)) {
        sfr::flight::initial_spin = false;
        set_white();
    }

    if (sfr::motor::spinning_up ) {
        vlogln("asking it to spin up: ");
        spinup();
    }

    if (sfr::motor::controller_on && sfr::imu::failed_init != false) {
       // sfr::controller::record_data = true;
        control();
    }

    if (sfr::motor::spin_down) {
        esc.write(0);
        sfr::motor::controller_on = false;
        sfr::motor::spin_down = false;
        sfr::motor::spinning_up = false;
    }
}

void MotorControlTask::spinup() {
    vlogln("spin up called");

    if (millis() - last_write > constants::motor::spinup_increment) {
        vlog("increasing pulse width");
        int val = map(sfr::motor::pulse_width, 0, 1000, 0, 180);
        esc.write(val);
        sfr::motor::pulse_width++;
        last_write = millis();
        vlogln(sfr::motor::pulse_width);
    }

    if (sfr::motor::pulse_width == 1) {
        esc.write(100);
        sfr::motor::spinning_up = false;
        sfr::motor::controller_on = true;
    }
}

void MotorControlTask::control() {
    vlogln("Controls called");
    // define current values
    error_curr = 4 - sfr::imu::gyro_z;
    time_curr = millis();

    sfr::imu::failed_init = true;
    if (sfr::imu::failed_init == false){

            // calculate PID terms
        proportional = Kp * error_curr;
        derivative = Kd * (error_curr - error_prev) / (time_curr - time_prev);

        // send electic pulse based on PID (range from 0 to 1000)
        vlogln(esc_prev);
        T = proportional + derivative;
        duty_cycle = (.043788 * T) + esc_prev;
        vlogln("T: " + String(T));
        vlogln("duty cycle: " + String(duty_cycle));

        if (duty_cycle < 1180.00) {
            duty_cycle = 1180.00;
        } else if (duty_cycle > 1920.00) {
            duty_cycle = 1920.00;
        }
        // convert duty cycle to angle for esc
        
    }else{ // open loop
        duty_cycle = 1800;
    }

    angle = map(duty_cycle, 1000, 2000, 0, 180);
    vlogln("ANGLE: " + String(angle));
    // write to esc
    esc.write(angle);
    

        // store values to be recorded
    sfr::controller::record_error = error_curr;
    sfr::controller::record_delta_error = error_curr - error_prev;
    sfr::controller::record_delta_time = time_curr - time_prev;
    sfr::controller::record_duty_cycle = duty_cycle;
    sfr::controller::record_angle = angle;
    sfr::controller::record_prop = proportional;
    sfr::controller::record_derivative = derivative;
    // integral should go here to but thats not in yet

    esc_prev = duty_cycle;
    vlogln(esc_prev);
    // set current as previous for next loop
    time_prev = time_curr;
    error_prev = error_curr;

    // vlogln("control done");
}