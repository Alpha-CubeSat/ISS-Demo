/**
 * @file sfr.hpp
 * @author csg83, vsc32
 *
 * @brief State field registry for global state management
 */

#ifndef SFR_HPP
#define SFR_HPP

#include "MissionMode.hpp"
#include "queue.hpp"

namespace sfr {
    namespace mission {
        extern InitialSpinupMode initial_spinup_class;
        extern StandbyMode standby_class;
        extern ArmedMode armed_class;
        extern DeploymentMode deployment_class;
        extern DespinMode despin_class;
        extern ControllerSpinupMode controller_spinup_class;
        extern OpenLoopMode open_loop_class;
        extern AutomatedSequenceMode automated_sequence_class;

        extern MissionMode *initial_spinup;
        extern MissionMode *standby;
        extern MissionMode *armed;
        extern MissionMode *deployment;
        extern MissionMode *despin;
        extern MissionMode *controller_spinup;
        extern MissionMode *open_loop;
        extern MissionMode *automated_sequence;

        extern MissionMode *mode;

        extern uint32_t timestamp;

        extern bool began_first_burn;
        extern bool began_second_burn;

        extern bool burned_first;
        extern bool burned_second;

        extern Queue events;

    } // namespace mission
    namespace ir {
        extern bool is_armed;
        extern bool was_invalid;

    } // namespace ir
    namespace motor {
        extern bool began_initial_spin;
        extern bool controller_on;

    } // namespace motor

    namespace imu {
        extern bool failed_init;
        extern bool failed_read;

        extern float accel_x;
        extern float accel_y;
        extern float accel_z;

        extern float gyro_x;
        extern float gyro_y;
        extern float gyro_z;

    } // namespace imu
    namespace sd {
        extern bool failed_init;
        extern char const *log_filename;

    } // namespace sd

    namespace controller {
        extern float record_angle;
        extern float record_duty_cycle;
        extern float record_error;
        extern float record_delta_error;
        extern float record_delta_time;
        extern float record_prop;
        extern float record_derivative;
        extern float record_integral;

        extern bool record_data;

    } // namespace controller
} // namespace sfr

#endif