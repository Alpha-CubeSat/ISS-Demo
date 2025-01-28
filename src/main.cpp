#include <Arduino.h>

#include "MissionMode.hpp"
#include "constants.hpp"
#include "pins.hpp"
#include "sfr.hpp"

void set_automated() {
    set_purple();
}

void setup() {
    Serial.begin(9600);

    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);

    pinMode(BUTTON_PIN, INPUT);
    attachInterrupt(BUTTON_PIN, set_automated, FALLING);

    sfr::mission::mode->enter();
}

void loop() {
    vlogln(F("-------------------- START LOOP --------------------"));

    vlog(F("Mode: "));
    vlogln(sfr::mission::mode->get_name());

    // vlog("SD: ");
    // vlogln(sfr)

    // uint32_t cycle_start = millis();

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
    delay(5);
    // if (millis() - cycle_start < 50) {
    //     delay();
    // }

    // vlogln(F("--------------------- END LOOP ---------------------"));
}