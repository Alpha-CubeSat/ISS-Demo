#include "IRControlTask.hpp"

#include <IRremote.hpp>

#include "sfr.hpp"
#include "constants.hpp"

void IRControlTask::begin() {
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
    case ARM_BUTTON:
        setGreen();
        sfr::ir::is_armed = true;
        vlogln("Lower Left");
        break;
    case SPIN_BUTTON:
        setBlue();
        sfr::motor::spinning_up = true;
        vlogln("Lower Right");
        break;
    case DEPLOY_BUTTON:
        setBlue();
        vlogln("Upper Left");
        break;
    case DESPIN_BUTTON:
        setBlue();
        sfr::motor::spin_down = true;
        vlogln("Upper Right");
        break;
    default:
        vlogln(IrReceiver.decodedIRData.command);
        break;
    }
}

void IRControlTask::handle_overflow() {
    IrReceiver.stopTimer();
    IrReceiver.restartTimer(100000);
}