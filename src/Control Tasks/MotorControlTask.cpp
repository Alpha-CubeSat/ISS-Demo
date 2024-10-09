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
     if (sfr::motor::spinning_up) {
        vlogln("asking it to spin up: ");
        spinup();
    }

    if(sfr::motor::controller_on){
        control();
    }

    if (sfr::motor::spin_down) {
        esc.write(0);

        sfr::motor::pulse_width_angle = 100;
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
    
    if (sfr::motor::pulse_width == 400) {
        sfr::motor::spinning_up = false;
        sfr::motor::controller_on = true;
    }
}

void MotorControlTask::control() {

    vlogln("Controls Called");
    
    //define current values
    error_curr = 4 - sfr::imu::gyro_z; 
    time_curr = millis();

    //calculate PID terms
    proportional = Kp* error_curr;
    derivative = Kd * (error_curr-error_prev)/(time_curr-time_prev);

    //send electic pulse based on PID (range from 0 to 1000)
    duty_cycle = proportional + derivative;
    if(duty_cycle < 600){
        duty_cycle = 600;
    }else if(duty_cycle>1000){
        duty_cycle =1000;
    }
    //convert duty cycle to angle for esc
    angle = map(duty_cycle, 0, 1000, 0, 180);

    //write to esc
    esc.write(angle);

    vlogln("control done");
    
}