#include "MotorControlTask.hpp"


MotorControlTask::MotorControlTask() {
    pwm.setClockDivider(1, false);
    pwm.timer(0, 8, 60000, false); 
}


void MotorControlTask::execute() {

}