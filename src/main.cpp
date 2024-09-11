#include <Arduino.h>

#include "constants.hpp"

#include "Control Tasks/IRControlTask.hpp"
#include "Control Tasks/MotorControlTask.hpp"

IRControlTask ir_control_task;
MotorControlTask motor_control_task;

void setup() {
    Serial.begin(9600);
}

void loop() {
    ir_control_task.execute();
    motor_control_task.execute();
}