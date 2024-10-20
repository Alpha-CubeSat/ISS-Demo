#ifndef MOTOR_CONTROL_TASK_HPP
#define MOTOR_CONTROL_TASK_HPP

#include <Servo.h>

class MotorControlTask {
public:
    void begin();
    void execute();

private:
    void spinup();

    Servo esc;
    unsigned long last_write;
};

#endif