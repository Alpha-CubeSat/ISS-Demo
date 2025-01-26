
#include "MissionMode.hpp"
#include "Monitors/IMUMonitor.hpp"
#include "constants.hpp"
#include "pins.hpp"
#include "sfr.hpp"

#include "Control Tasks/IRControlTask.hpp"
#include "Control Tasks/MotorControlTask.hpp"
#include "Control Tasks/SDControlTask.hpp"
#include "Monitors/IMUMonitor.hpp"

IMUMonitor imu_monitor;
IRControlTask ir_control_task;
MotorControlTask motor_control_task;
SDControlTask sd_control_task;

void MissionMode::execute() {
    imu_monitor.execute();
    motor_control_task.execute();
    sd_control_task.execute();
    ir_control_task.execute();
}

void StandbyMode::enter() {
    set_white();

    imu_monitor.begin();
    motor_control_task.begin();
    sd_control_task.begin();
    ir_control_task.begin();
}

void StandbyMode::execute() {
    MissionMode::execute();
}

void StandbyMode::exit() {
}

void ArmedMode::enter() {
    set_green();
    arm_timer.start(constants::ir::arm_timeout);
    sfr::ir::is_armed = true;
}

void ArmedMode::execute() {
    MissionMode::execute();

    if (arm_timer.is_elapsed()) {
        set_yellow();
        to_mode(sfr::mission::standby);
    }
}

void ArmedMode::exit() {
    arm_timer.reset();
}

void DeploymentMode::enter() {
    set_blue();
    deploy_timer.start(constants::mission::deployment_length);
}

void DeploymentMode::execute() {
    MissionMode::execute();
}

void DeploymentMode::exit() {
    deploy_timer.reset();
}

void DespinMode::enter() {
    set_blue();
    despin_timer.start(constants::mission::despin_length);
}

void DespinMode::execute() {
    MissionMode::execute();
}

void DespinMode::exit() {
}

void ControllerSpinupMode::enter() {
    set_blue();
    controller_timeout_timer.start(constants::mission::controller_timeout_length);
    sfr::motor::controller_on = true;
}

void ControllerSpinupMode::execute() {
    MissionMode::execute();
}

void ControllerSpinupMode::exit() {
}

void OpenLoopMode::enter() {
    set_purple();
    open_loop_timer.start(constants::mission::open_loop_length);
}

void OpenLoopMode::execute() {
    MissionMode::execute();
}

void OpenLoopMode::exit() {
}

void to_mode(MissionMode *mode) {
    sfr::mission::mode->exit();
    sfr::mission::mode = mode;
    sfr::mission::mode->enter();
}