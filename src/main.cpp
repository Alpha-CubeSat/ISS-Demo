#include <Arduino.h>

#include "constants.hpp"

#include "sfr.hpp"
#include "Monitors/IMUMonitor.hpp"
#include "Control Tasks/IRControlTask.hpp"
#include "Control Tasks/MotorControlTask.hpp"

IMUMonitor imu_monitor;
IRControlTask ir_control_task;
MotorControlTask motor_control_task;

void setup() {
    Serial.begin(9600);
    imu_monitor.begin();

    delay(5000);
}

void loop() {
    Serial.println(F("-------------------- START LOOP --------------------"));

    Serial.print(F("Gyro X: "));
    Serial.println(sfr::imu::gyro_x);

    Serial.print(F("Gyro Y: "));
    Serial.println(sfr::imu::gyro_y);

    Serial.print(F("Gyro Z: "));
    Serial.println(sfr::imu::gyro_z);

    Serial.print(F("Accel X: "));
    Serial.println(sfr::imu::accel_x);

    Serial.print(F("Accel Y: "));
    Serial.println(sfr::imu::accel_y);

    Serial.print(F("Accel Z: "));
    Serial.println(sfr::imu::accel_z);

    imu_monitor.execute();
    ir_control_task.execute();
    motor_control_task.execute();

    Serial.println(F("-------------------- END LOOP --------------------"));
}