
#include "MissionMode.hpp"
#include "Monitors/IMUMonitor.hpp"
#include "constants.hpp"
#include "sfr.hpp"

void MissionMode::execute() {
    // imu_monitor.execute();
}

void StandbyMode::enter() {
    set_white();
}

void StandbyMode::execute() {
}

void StandbyMode::exit() {
}

void ArmedMode::enter() {
    set_green();
    arm_timer.start(constants::ir::arm_timeout);
    sfr::ir::is_armed = true;
}

void ArmedMode::execute() {
}

void ArmedMode::exit() {
}

void DeploymentMode::enter() {
    set_blue();
    deploy_timer.start(constants::mission::deployment_length);
}

void DeploymentMode::execute() {
}

void DeploymentMode::exit() {
}

void DespinMode::enter() {
    set_blue();
    despin_timer.start(constants::mission::despin_length);
}

void DespinMode::execute() {
}

void DespinMode::exit() {
}

void ControllerSpinupMode::enter() {
    set_blue();
    controller_timeout_timer.start(constants::mission::controller_timeout_length);
    sfr::motor::controller_on = true;
}

void ControllerSpinupMode::execute() {
}

void ControllerSpinupMode::exit() {
}

void OpenLoopMode::enter() {
    set_purple();
    open_loop_timer.start(constants::mission::open_loop_length);
}

void OpenLoopMode::execute() {
}

void OpenLoopMode::exit() {
}

void to_mode(MissionMode *mode) {
    sfr::mission::mode = mode;
    sfr::mission::mode->enter();
}