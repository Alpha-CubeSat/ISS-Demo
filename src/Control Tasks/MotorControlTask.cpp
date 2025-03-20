/**
 * @file MotorControlTask.cpp
 * @author csg83, vsc32
 *
 * @brief Handles controller logic based on SFR data
 */

#include "MotorControlTask.hpp"
#include "constants.hpp"
#include "pins.hpp"
#include "sfr.hpp"

#include <Arduino.h>

void MotorControlTask::begin() {
    esc.attach(PWM_PIN, 1000, 2000);
    esc.write(0);
}

void MotorControlTask::spin_up(int dc) {
    esc.write(0);
    sfr::controller::record_duty_cycle = dc;
    esc.write(map(dc, 1000, 2000, 0, 180));
}

void MotorControlTask::spin_down() {
    sfr::motor::controller_on = false;
    duty_cycle = 0;
    sfr::controller::record_duty_cycle = duty_cycle;
    esc.write(duty_cycle);
}

void MotorControlTask::execute_controller() {
    // vlogln("Controls called");
    //  define current values
    error_curr = 4 - abs(sfr::imu::gyro_z);
    time_curr = millis();

    if (sfr::imu::failed_init == false || sfr::imu::failed_read == false) {
        // calculate PD terms
        proportional = Kp * error_curr;
        // derivative = Kd * (error_curr - error_prev) / (time_curr - time_prev);

        // send electic pulse based on PID (range from 0 to 1000)
        // vlogln(esc_prev);
        T = proportional;// + derivative;
        duty_cycle = (.043788 * T) + esc_prev; // TODO Shashank look at
        // vlogln("T: " + String(T));
        // vlogln("duty cycle: " + String(duty_cycle));

        if (duty_cycle < 1180.00) {
            duty_cycle = 1180.00;
        } else if (duty_cycle > 2000.00) {
            duty_cycle = 2000.00;
        }
        // convert duty cycle to angle for esc

    } else { // open loop
        duty_cycle = 1600; // calc a reasonable value
    }

    angle = map(duty_cycle, 1000, 2000, 0, 180);
    // vlogln("ANGLE: " + String(angle));
    //  write to esc
    esc.write(angle);

    // store values to be recorded
    sfr::controller::record_error = error_curr;
    sfr::controller::record_delta_error = error_curr - error_prev;
    sfr::controller::record_delta_time = time_curr - time_prev;
    sfr::controller::record_duty_cycle = duty_cycle;
    sfr::controller::record_angle = angle;
    sfr::controller::record_prop = proportional;
    sfr::controller::record_derivative = derivative;

    esc_prev = duty_cycle;
    // vlogln(esc_prev);
    //  set current as previous for next loop
    time_prev = time_curr;
    error_prev = error_curr;

    // vlogln("control done");
}