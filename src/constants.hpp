#define PWM_PIN 10
#define IR_PIN 11

#define RED_LED_PIN 2
#define GREEN_LED_PIN 8
#define BLUE_LED_PIN 9

#define UPPER_RIGHT 0xA
#define LOWER_RIGHT 0xB
#define UPPER_LEFT 0xC
#define LOWER_LEFT 0xD
#define MUTE_BUTTON 0XE
#define POWER_BUTTON 0xF
#define CC_BUTTON 0xCC
#define OK_BUTTON 0x18

namespace constants {
    namespace motor {
        constexpr int spinup_increment = 150;
    }
}