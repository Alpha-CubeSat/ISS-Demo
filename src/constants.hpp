#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <Arduino.h>

#ifdef VERBOSE
#define vlogln(...) Serial.println(__VA_ARGS__)
#define vlog(...) Serial.print(__VA_ARGS__)
#define vlogf(...) Serial.printf(__VA_ARGS__)
#else
#define vlogln(...)
#define vlog(...)
#define vlogf(...)
#endif

// Pins

#define PWM_PIN 10
#define IR_PIN 11
#define SD_PIN 4

#define GATE_PIN A4
#define BUTTON_PIN 5

#define RED_LED_PIN 2
#define GREEN_LED_PIN 8
#define BLUE_LED_PIN 9

// IR remote buttons

#define UPPER_RIGHT 0xA
#define LOWER_RIGHT 0xB
#define UPPER_LEFT 0xC
#define LOWER_LEFT 0xD
#define MUTE_BUTTON 0XE
#define POWER_BUTTON 0xF
#define CC_BUTTON 0xCC
#define OK_BUTTON 0x18

#define ARM_BUTTON UPPER_RIGHT
#define CONTROLLER_SPIN_BUTTON UPPER_LEFT
#define DEPLOY_BUTTON LOWER_LEFT
#define DESPIN_BUTTON LOWER_RIGHT

// LED colors

inline void set_white() {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
}

inline void set_blue() {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, LOW);
}

inline void set_green() {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
}

inline void set_yellow() {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
}

inline void set_purple() {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, LOW);
}

namespace constants {
    namespace flight {
        constexpr unsigned long initial_hold_time = 5000;
        constexpr unsigned long initial_spin_time = 10000; // TODO: This is kinda hacky but I'm lazy rn
    } // namespace flight
    namespace ir {
        constexpr unsigned long arm_timeout = 2000;
        constexpr unsigned long deploy_led_timeout = 3000;
    } // namespace ir
    namespace motor {
        constexpr int spinup_increment = 150;
    }
    namespace imu {
        constexpr uint8_t max_failed_reads = 10;
    }

    namespace sd {
        constexpr char const *boot_filename = "boot.txt";
    }
} // namespace constants

#endif