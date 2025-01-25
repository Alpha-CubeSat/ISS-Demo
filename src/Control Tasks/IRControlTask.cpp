#include "IRControlTask.hpp"

#include <IRremote.hpp>

#include "constants.hpp"
#include "sfr.hpp"

void IRControlTask::begin() {
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void IRControlTask::execute() {
    // Deploy
    if (deploy_led_timer.is_elapsed()) {
        digitalWrite(GATE_PIN, HIGH);
        delay(1);
        digitalWrite(GATE_PIN, LOW);

        set_white();
    }

    // Handle arming timeout
    if (arm_timer.is_elapsed()) {
        set_yellow();
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
    // Ignore repeat commands (except for Arm)
    if (button_selected == IrReceiver.decodedIRData.command && button_selected != ARM_BUTTON) {
        return;
    }
    // Ignore >2 action commands after an Arm
    if (sfr::ir::is_armed && button_selected != ARM_BUTTON && IrReceiver.decodedIRData.command != ARM_BUTTON) {
        return;
    }
    button_selected = IrReceiver.decodedIRData.command;

    switch (button_selected) {
    case ARM_BUTTON:
        set_green();
        sfr::ir::is_armed = true;
        arm_timer.start(constants::ir::arm_timeout);

        vlogln("Upper Right");
        break;
    case CONTROLLER_SPIN_BUTTON:
        if (sfr::ir::is_armed) {
            set_blue();
            sfr::motor::spinning_up = true;
        } else {
            set_yellow();
        }

        vlogln("Lower Right");
        break;
    case DEPLOY_BUTTON:
        if (sfr::ir::is_armed) {
            set_blue();

            sfr::ir::is_armed = false;

            deploy_led_timer.start(constants::ir::deploy_led_timeout);
        } else {
            set_yellow();
        }

        vlogln("Lower Left");
        break;
    case DESPIN_BUTTON:
        if (sfr::ir::is_armed) {
            set_blue();
            sfr::motor::spin_down = true;
        } else {
            set_yellow();
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