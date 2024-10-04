#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

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
#define SPIN_BUTTON UPPER_LEFT
#define DEPLOY_BUTTON LOWER_LEFT
#define DESPIN_BUTTON LOWER_RIGHT

namespace constants {
    namespace motor {
        constexpr int spinup_increment = 150;
    }

    namespace sd {
        constexpr char const *filename = "data.csv";
    }
}

#endif