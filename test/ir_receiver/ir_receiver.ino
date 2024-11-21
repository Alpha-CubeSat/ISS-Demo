#include <Arduino.h>
#include <IRremote.hpp>

#define IR_PIN 11

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

