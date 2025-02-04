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
        to_mode(sfr::mission::armed);
        break;
    case CONTROLLER_SPIN_BUTTON:
        if (sfr::ir::is_armed) {
            to_mode(sfr::mission::controller_spinup);
        } else {
            set_yellow();
        }
        break;
    case DEPLOY_BUTTON:
        if (sfr::ir::is_armed) {
            to_mode(sfr::mission::deployment);
        } else {
            set_yellow();
        }
        break;
    case DESPIN_BUTTON:
        if (sfr::ir::is_armed) {
            to_mode(sfr::mission::despin);
        } else {
            set_yellow();
        }
        break;
    case OPEN_LOOP_BUTTON:
        if (sfr::ir::is_armed) {
            to_mode(sfr::mission::open_loop);
        } else {
            set_yellow();
        }
        break;
    default:
        vlogln(IrReceiver.decodedIRData.command);
        break;
    }
}

Event IRControlTask::get_event(uint8_t button) {
    switch (button) {
    case ARM_BUTTON:
        return Event::arm_button_received;
    case CONTROLLER_SPIN_BUTTON:
        return Event::cs_button_received;
    case DEPLOY_BUTTON:
        return Event::deploy_button_received;
    case DESPIN_BUTTON:
        return Event::despin_button_received;
    case OPEN_LOOP_BUTTON:
        return Event::open_loop_button_received;
    default:
        return Event::unknown_button_received;
    }
}

void IRControlTask::handle_overflow() {
    IrReceiver.stopTimer();
    IrReceiver.restartTimer(100000);
}