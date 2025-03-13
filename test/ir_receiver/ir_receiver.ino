#include <Arduino.h>
#include <IRremote.hpp>

#define IR_PIN 11

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
#define DESPIN_BUTTON UPPER_RIGHT
#define OPEN_LOOP_BUTTON LOWER_LEFT

// Alternative IR remote buttons

#define UPPER_RIGHT_ALT 8
#define LOWER_RIGHT_ALT 2
#define UPPER_LEFT_ALT 0
#define LOWER_LEFT_ALT 3
#define MUTE_BUTTON_ALT 1
#define POWER_BUTTON_ALT 9
#define CC_BUTTON_ALT 57
#define OK_BUTTON_ALT 68

#define ARM_BUTTON_ALT POWER_BUTTON_ALT
#define CONTROLLER_SPIN_BUTTON_ALT UPPER_LEFT_ALT
#define DEPLOY_BUTTON_ALT LOWER_RIGHT_ALT
#define DESPIN_BUTTON_ALT UPPER_RIGHT_ALT
#define OPEN_LOOP_BUTTON_ALT LOWER_LEFT_ALT

void handleOverflow() {
    IrReceiver.stopTimer();
    IrReceiver.restartTimer(100000);
}

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
    if (IrReceiver.decode()) {
        if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
            handleOverflow();
        } else { 
            IrReceiver.resume();
            switch (IrReceiver.decodedIRData.command) {
            case 0xA:
                Serial.println("Upper Right");
                break;
            case 0xB:
                Serial.println("Lower Right");
                break;
            case 0xC:
                Serial.println("Upper Left");
                break;
            case 0xD:
                Serial.println("Lower Left");
                break;
            case 0xE:
                Serial.println("Mute Button");
                break;
            case 0xF:
                Serial.println("Power Button");
                break;
            case 0x1C:
                Serial.println("CC Button");
                break;
            case 0x18:
                Serial.println("OK Button");
                break;
            default:
                Serial.print("Unknown Command: ");
                Serial.println(IrReceiver.decodedIRData.command);
                break;
            }
        }
    }
}

