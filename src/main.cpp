#include <Arduino.h>

#include "constants.hpp"
#include "pins.hpp"
#include "MissionMode.hpp"
#include "sfr.hpp"



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

    sfr::mission::mode->enter();
    delay(5000);
}

void loop() {
    vlogln(F("-------------------- START LOOP --------------------"));

    vlog(F("Mode: "));
    vlogln(sfr::mission::mode->get_name());

    sfr::mission::mode->execute();

    // vlog(F("Gyro X: "));
    // vlogln(sfr::imu::gyro_x);

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

    // vlogln(F("--------------------- END LOOP ---------------------"));
}