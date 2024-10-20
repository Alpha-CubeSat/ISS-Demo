#include "IRControlTask.hpp"

#include <IRremote.hpp>

#include "constants.hpp"
#include "sfr.hpp"

void IRControlTask::begin() {
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void IRControlTask::execute() {
    // Deploy
    if (sfr::ir::is_deploying && (millis() - sfr::ir::armed_start > constants::ir::arm_timeout)) {
        setWhite();
        sfr::ir::is_deploying = false;
        // TODO: Actuate filament
    }

    // Handle arming timeout
    if (sfr::ir::is_armed && (millis() - sfr::ir::armed_start > constants::ir::arm_timeout)) {
        setYellow();
        sfr::ir::is_armed = false;
    }

    // Parse any commands sent
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
        sfr::ir::armed_start = millis();

        vlogln("Upper Right");
        break;
    case SPIN_BUTTON:
        if (sfr::ir::is_armed) {
            setBlue();
            sfr::motor::spinning_up = true;
        } else {
            setYellow();
        }

        vlogln("Lower Right");
        break;
    case DEPLOY_BUTTON:
        if (sfr::ir::is_armed) {
            setBlue();

            sfr::ir::is_armed = false;

            sfr::ir::is_deploying = true;
            sfr::ir::deploy_start = millis();
        } else {
            setYellow();
        }

        vlogln("Lower Left");
        break;
    case DESPIN_BUTTON:
        if (sfr::ir::is_armed) {
            setBlue();
            sfr::motor::spin_down = true;
        } else {
            setYellow();
        }

        vlogln("Lower Right");
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