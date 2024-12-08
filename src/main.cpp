#include <Arduino.h>

#include "constants.hpp"

#include "Control Tasks/IRControlTask.hpp"
#include "Control Tasks/MotorControlTask.hpp"
#include "Control Tasks/SDControlTask.hpp"
#include "Monitors/IMUMonitor.hpp"
#include "sfr.hpp"

IMUMonitor imu_monitor;
IRControlTask ir_control_task;
MotorControlTask motor_control_task;
SDControlTask sd_control_task;

void set_automated() {
    sfr::flight::automated = true;
    set_purple();
}

void setup() {
    Serial.begin(9600);

    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);

    pinMode(BUTTON_PIN, INPUT);
    attachInterrupt(BUTTON_PIN, set_automated, FALLING);

    set_blue();

    imu_monitor.begin();
    ir_control_task.begin();
    motor_control_task.begin();
    sd_control_task.begin();
}

void loop() {
    vlogln(F("-------------------- START LOOP --------------------"));

    imu_monitor.execute();
    // if (!sfr::flight::automated) {
    ir_control_task.execute();
    // }
    motor_control_task.execute();
    sd_control_task.execute();

    vlog(F("Gyro X: "));
    vlogln(sfr::imu::gyro_x);

    // vlog(F("Gyro Y: "));
    // vlogln(sfr::imu::gyro_y);

    // vlog(F("Gyro Z: "));
    // vlogln(sfr::imu::gyro_z);

    // vlog(F("Accel X: "));
    // vlogln(sfr::imu::accel_x);

    // vlog(F("Accel Y: "));
    // vlogln(sfr::imu::accel_y);

    // vlog(F("Accel Z: "));
    // vlogln(sfr::imu::accel_z);

    vlogln(F("--------------------- END LOOP ---------------------"));
}