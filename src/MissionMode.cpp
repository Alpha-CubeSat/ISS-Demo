
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
MotorControlTask motor_control_task;
SDControlTask sd_control_task;
IRControlTask ir_control_task;

void MissionMode::execute() {
    imu_monitor.execute();
    sd_control_task.execute();
    if (sfr::mission::mode->get_id() != 7) {
        ir_control_task.execute();
    }

    if (sfr::motor::controller_on) {
        motor_control_task.execute_controller();
    }
}

void MissionMode::exit() {
}

void InitialSpinupMode::enter() {
    set_blue();
    digitalWrite(GUIDE_LASER_PIN, HIGH);

    imu_monitor.begin();
    motor_control_task.begin();
    sd_control_task.begin();
    ir_control_task.begin();

    initial_spinup_timer.start(constants::timer::initial_spinup_duration);
}

void InitialSpinupMode::execute() {
    if (sfr::imu::failed_init) {
        imu_monitor.begin();
    }
    if (sfr::sd::failed_init) {
        sd_control_task.begin();
    }
    MissionMode::execute();

    if (!sfr::motor::began_initial_spin && initial_spinup_timer.is_past(3000)) {
        motor_control_task.spin_up(constants::motor::initial_spin_dc);
        sfr::motor::began_initial_spin = true;
    }

    if (initial_spinup_timer.is_elapsed()) {
        to_mode(sfr::mission::standby);
    }
}

void StandbyMode::enter() {
    set_white();
}

void StandbyMode::execute() {
    MissionMode::execute();
}

void ArmedMode::enter() {
    set_green();
    arm_timer.start(constants::timer::arm_timeout);
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
    sfr::ir::is_armed = false;
}

void DeploymentMode::enter() {
    set_blue();
    deploy_timer.start(constants::timer::deployment_total_duration);
    sfr::motor::controller_on = false;
}

void DeploymentMode::execute() {
    MissionMode::execute();

    if (!sfr::mission::began_deployment && deploy_timer.is_past(constants::timer::deployment_standby_duration)) {
        digitalWrite(GUIDE_LASER_PIN, LOW);
        digitalWrite(GATE_PIN, HIGH);
        sfr::mission::began_deployment = true;
    }

    if (!sfr::mission::deployed && sfr::mission::began_deployment && deploy_timer.is_past(constants::timer::deployment_standby_duration + constants::timer::deployment_actuate_duration)) {
        digitalWrite(GATE_PIN, LOW);
        sfr::mission::deployed = true;
    }

    if (deploy_timer.is_elapsed()) {
        to_mode(sfr::mission::standby);
    }
}

void DeploymentMode::exit() {
    deploy_timer.reset();
}

void DespinMode::enter() {
    set_blue();
    despin_timer.start(constants::timer::despin_duration);
    sfr::motor::controller_on = false;
    motor_control_task.spin_down();
}

void DespinMode::execute() {
    MissionMode::execute();

    if (despin_timer.is_elapsed()) {
        to_mode(sfr::mission::standby);
    }
}

void ControllerSpinupMode::enter() {
    set_blue();
    controller_timeout_timer.start(constants::timer::controller_timeout);
    sfr::motor::controller_on = true;
}

void ControllerSpinupMode::execute() {
    MissionMode::execute();

    if (controller_timeout_timer.is_elapsed()) {
        to_mode(sfr::mission::standby);
    }
}

void OpenLoopMode::enter() {
    set_purple();
    motor_control_task.spin_up(constants::motor::open_loop_spin_dc);
    open_loop_timer.start(constants::timer::open_loop_duration);
}

void OpenLoopMode::execute() {
    MissionMode::execute();

    if (open_loop_timer.is_elapsed()) {
        to_mode(sfr::mission::standby);
    }
}

void AutomatedSequenceMode::enter() {
    set_blue();
    sfr::motor::controller_on = false;
}

void AutomatedSequenceMode::execute() {
    MissionMode::execute();

    switch (current_action) {
    case SPINUP:
        as_open_loop_spinup();
        break;
    case DEPLOY:
        as_deploy();
        break;
    case DESPIN:
        as_despin();
        break;
    }
}

void AutomatedSequenceMode::as_open_loop_spinup() {
    if (!as_open_loop_init) {
        motor_control_task.spin_up(constants::motor::open_loop_spin_dc);
        open_loop_timer.start(constants::timer::open_loop_duration);
        as_open_loop_init = true;
    }

    if (open_loop_timer.is_elapsed()) {
        current_action = DEPLOY;
    }
}

void AutomatedSequenceMode::as_deploy() {
    if (!as_deploy_init) {
        deploy_timer.start(constants::timer::deployment_total_duration);
        as_deploy_init = true;
    }

    if (!sfr::mission::began_deployment && deploy_timer.is_past(constants::timer::deployment_standby_duration)) {
        digitalWrite(GUIDE_LASER_PIN, LOW);
        digitalWrite(GATE_PIN, HIGH);
        sfr::mission::began_deployment = true;
    }

    if (!sfr::mission::deployed && sfr::mission::began_deployment && deploy_timer.is_past(constants::timer::deployment_standby_duration + constants::timer::deployment_actuate_duration)) {
        digitalWrite(GATE_PIN, LOW);
        sfr::mission::deployed = true;
    }

    if (deploy_timer.is_elapsed()) {
        current_action = DESPIN;
    }
}

void AutomatedSequenceMode::as_despin() {
    if (!as_despin_init) {
        despin_timer.start(constants::timer::despin_duration);
        motor_control_task.spin_down();
        as_despin_init = true;
    }
}

void to_mode(MissionMode *mode) {
    sfr::mission::mode->exit();
    sfr::mission::mode = mode;
    sfr::mission::mode->enter();
}