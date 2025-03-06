#include "IRControlTask.hpp"

#include <IRremote.hpp>

#include "constants.hpp"
#include "pins.hpp"

void IRControlTask::begin() {
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}

void IRControlTask::execute() {
    // Parse any commands sent
    if (IrReceiver.decode()) {
        if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
            sfr::mission::events.enqueue(Event::ir_overflow_detected);
            handle_overflow();
        } else {
            IrReceiver.resume();
            parse_command();
        }
    }
}

void IRControlTask::parse_command() {
    sfr::mission::events.enqueue(get_event(IrReceiver.decodedIRData.command));

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
    case ARM_BUTTON_ALT:
        to_mode(sfr::mission::armed);
        break;
    case CONTROLLER_SPIN_BUTTON:
    case CONTROLLER_SPIN_BUTTON_ALT:
        if (sfr::ir::is_armed) {
            to_mode(sfr::mission::controller_spinup);
        } else {
            sfr::ir::was_invalid = true;
        }
        break;
    case DEPLOY_BUTTON:
    case DEPLOY_BUTTON_ALT:
        if (sfr::ir::is_armed) {
            to_mode(sfr::mission::deployment);
        } else {
            sfr::ir::was_invalid = true;
        }
        break;
    case DESPIN_BUTTON:
    case DESPIN_BUTTON_ALT:
        if (sfr::ir::is_armed) {
            to_mode(sfr::mission::despin);
        } else {
            sfr::ir::was_invalid = true;
        }
        break;
    case OPEN_LOOP_BUTTON:
    case OPEN_LOOP_BUTTON_ALT:
        if (sfr::ir::is_armed) {
            to_mode(sfr::mission::open_loop);
        } else {
            sfr::ir::was_invalid = true;
        }
        break;
    default:
        sfr::ir::was_invalid = true;
        vlogln(IrReceiver.decodedIRData.command);
        break;
    }
}

Event IRControlTask::get_event(uint8_t button) {
    switch (button) {
    case ARM_BUTTON:
    case ARM_BUTTON_ALT:
        return Event::arm_button_received;
    case CONTROLLER_SPIN_BUTTON:
    case CONTROLLER_SPIN_BUTTON_ALT:
        return Event::cs_button_received;
    case DEPLOY_BUTTON:
    case DEPLOY_BUTTON_ALT:
        return Event::deploy_button_received;
    case DESPIN_BUTTON:
    case DESPIN_BUTTON_ALT:
        return Event::despin_button_received;
    case OPEN_LOOP_BUTTON:
    case OPEN_LOOP_BUTTON_ALT:
        return Event::open_loop_button_received;
    default:
        return Event::unknown_button_received;
    }
}

void IRControlTask::handle_overflow() {
    IrReceiver.stopTimer();
    IrReceiver.restartTimer(100000);
}