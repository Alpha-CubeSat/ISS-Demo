/**
 * @file pins.hpp
 * @author csg83
 *
 * @brief Pin definitions and functions
 */

#ifndef PINS_HPP
#define PINS_HPP

#define PWM_PIN 10
#define IR_PIN 11
#define SD_PIN 4

#define GATE_PIN A4
#define BUTTON_PIN 5
#define GUIDE_LASER_PIN A5

#define RED_LED_PIN A0
#define GREEN_LED_PIN A1
#define BLUE_LED_PIN A2

// IR remote buttons

#define UPPER_RIGHT 0xA
#define LOWER_RIGHT 0xB
#define UPPER_LEFT 0xC
#define LOWER_LEFT 0xD
#define MUTE_BUTTON 0xE
#define POWER_BUTTON 0xF
#define CC_BUTTON 0x1C
#define OK_BUTTON 0x18

#define ARM_BUTTON POWER_BUTTON
#define CONTROLLER_SPIN_BUTTON UPPER_LEFT
#define DEPLOY_BUTTON LOWER_RIGHT
#define DESPIN_BUTTON LOWER_LEFT
#define OPEN_LOOP_BUTTON MUTE_BUTTON

// Alternative IR remote buttons

#define UPPER_RIGHT_ALT 0
#define LOWER_RIGHT_ALT 1
#define UPPER_LEFT_ALT 2
#define LOWER_LEFT_ALT 3
#define MUTE_BUTTON_ALT 9
#define POWER_BUTTON_ALT 8
#define CC_BUTTON_ALT 57
#define OK_BUTTON_ALT 68

#define ARM_BUTTON_ALT POWER_BUTTON_ALT
#define CONTROLLER_SPIN_BUTTON_ALT UPPER_LEFT_ALT
#define DEPLOY_BUTTON_ALT LOWER_RIGHT_ALT
#define DESPIN_BUTTON_ALT LOWER_LEFT_ALT
#define OPEN_LOOP_BUTTON_ALT MUTE_BUTTON_ALT

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

inline void set_off() {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, HIGH);
}

#endif // PINS_HPP