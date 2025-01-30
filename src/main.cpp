#include <Arduino.h>

#include "MissionMode.hpp"
#include "constants.hpp"
#include "pins.hpp"
#include "sfr.hpp"

void set_automated() {
    to_mode(sfr::mission::automated_sequence);
}

uint32_t cycle_start, cycle_duration;

void setup() {
    Serial.begin(9600);

    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);

    pinMode(GUIDE_LASER_PIN, OUTPUT);

    pinMode(BUTTON_PIN, INPUT);
    // attachInterrupt(BUTTON_PIN, set_automated, FALLING);

    sfr::mission::mode->enter();
}

void loop() {
    vlogln("-------------------- START LOOP --------------------");

    vlogln("Mode: " + sfr::mission::mode->get_name());
    vlogln("Timestamp (ms): " + String(sfr::mission::timestamp) + "\n");

    vlogln("Angle: " + String(sfr::controller::record_angle) + "\n");

    vlogln("Gyro X (rad/s): " + String(sfr::imu::gyro_x));
    vlogln("Gyro Y (rad/s): " + String(sfr::imu::gyro_y));
    vlogln("Gyro Z (rad/s): " + String(sfr::imu::gyro_z) + "\n");

    vlogln("Accel X (m/s^2): " + String(sfr::imu::accel_x));
    vlogln("Accel Y (m/s^2): " + String(sfr::imu::accel_y));
    vlogln("Accel Z (m/s^2): " + String(sfr::imu::accel_z));

    cycle_start = millis();
    sfr::mission::mode->execute();
    sfr::mission::timestamp = millis();
    cycle_duration = sfr::mission::timestamp - cycle_start;

    if (cycle_duration < constants::mission::cycle_time) {
        delay(constants::mission::cycle_time - cycle_duration);
    }

    vlogln("--------------------- END LOOP ---------------------");
}