#ifndef MOTOR_CONTROL_TASK_HPP
#define MOTOR_CONTROL_TASK_HPP

#include <SAMD21turboPWM.h>


class MotorControlTask {
public:
    MotorControlTask();
    void execute();

private:
    TurboPWM pwm;

};

#endif