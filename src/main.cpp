#include <Arduino.h>

#include "constants.hpp"

#include "Monitors/IMUMonitor.hpp"

#include "Control Tasks/IRControlTask.hpp"
#include "Control Tasks/MotorControlTask.hpp"

IMUMonitor imu_monitor;
IRControlTask ir_control_task;
MotorControlTask motor_control_task;

void setup() {
    Serial.begin(9600);
    delay(5000);
}

void loop() {
    imu_monitor.execute();
    ir_control_task.execute();
    motor_control_task.execute();
}