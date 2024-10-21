#ifndef MOTOR_CONTROL_TASK_HPP
#define MOTOR_CONTROL_TASK_HPP

#include <Servo.h>

class MotorControlTask {
//controls constants
double error_curr = 0.0;
double error_prev = 0.0;
double duty_cycle = 0.0;
double angle = 0.0;
double time_curr = 0.0;
double time_prev = 0.0;

double Kd = 5;
double Kp = 5;
double proportional = 0.0;
double derivative = 0.0;
double pulse_width = 0.0;
double T = 0.0;
double esc_prev = 0.0;
IMUMonitor imu_monitor;
SDControlTask sdCard; 

public:
    void begin();
    void execute();

private:

    void spinup();
    void control();
    Servo esc;
    unsigned long last_write;
};

#endif