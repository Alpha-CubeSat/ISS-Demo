/**
 * @file MotorControlTask.hpp
 * @author csg83, vsc32
 *
 * @brief Handles controller logic based on SFR data
 */

#ifndef MOTOR_CONTROL_TASK_HPP
#define MOTOR_CONTROL_TASK_HPP

#include <Servo.h>

class MotorControlTask {
public:
    void begin();
    void execute_controller();
    void spin_up(int dc);
    void spin_down();

private:
    Servo esc;
    unsigned long last_write;

    // controls constants
    double error_curr = 0.0;
    double error_prev = 0.0;
    double duty_cycle = 0.0;
    double angle = 0.0;
    double time_curr = 0.0;
    double time_prev = 0.0;

    double Kd = 50;
    double Kp = 10000;
    double proportional = 0.0;
    double derivative = 0.0;
    double pulse_width = 0.0;
    double T = 0.0;
    double esc_prev = 0.0;
};

#endif // MOTOR_CONTROL_TASK_HPP