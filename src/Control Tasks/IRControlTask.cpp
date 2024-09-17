#include "IRControlTask.hpp"

#include <IRremote.hpp>

#include "sfr.hpp"
#include "constants.hpp"

IRControlTask::IRControlTask() {
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void IRControlTask::execute() {
    if (IrReceiver.decode()) {
        if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
            handle_overflow();
        } else {
            IrReceiver.resume();
            parse_command();
        }
    }
}

void IRControlTask::parse_command() {
    switch (IrReceiver.decodedIRData.command) {
    case LOWER_LEFT:
        Serial.println("Lower Left");
        break;
    case LOWER_RIGHT:
        Serial.println("Lower Right");
        break;
    case UPPER_LEFT:
        Serial.println("Upper Left");
        break;
    case UPPER_RIGHT:
        Serial.println("Upper Right");
        sfr::motor::spinning_up = true;
        break;
    case MUTE_BUTTON:
        Serial.println("Mute Button");
        break;
    case POWER_BUTTON:
        Serial.println("Power Button");
        break;
    case CC_BUTTON:
        Serial.println("CC Button");
        break;
    case OK_BUTTON:
        Serial.println("OK Button");
        break; 
    default:
        Serial.println(IrReceiver.decodedIRData.command);
        break;
    }
}

void IRControlTask::handle_overflow() {
    IrReceiver.stopTimer();
    IrReceiver.restartTimer(100000);
}