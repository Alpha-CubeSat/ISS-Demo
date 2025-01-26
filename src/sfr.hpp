#ifndef SFR_HPP
#define SFR_HPP

#include "MissionMode.hpp"

namespace sfr {
    namespace mission {
        extern InitialSpinupMode initial_spinup_class;
        extern StandbyMode standby_class;
        extern ArmedMode armed_class;
        extern DeploymentMode deployment_class;
        extern DespinMode despin_class;
        extern ControllerSpinupMode controller_spinup_class;
        extern OpenLoopMode open_loop_class;

        extern MissionMode *initial_spinup;
        extern MissionMode *standby;
        extern MissionMode *armed;
        extern MissionMode *deployment;
        extern MissionMode *despin;
        extern MissionMode *controller_spinup;
        extern MissionMode *open_loop;

        extern MissionMode *mode;

        extern bool began_deployment;
        extern bool deployed;
    } // namespace mission
    namespace flight {
        extern bool initial_hold;
        extern bool initial_spin;
        extern volatile bool automated;
    } // namespace flight
    namespace ir {
        extern bool is_armed;
        extern unsigned long armed_start;

        extern unsigned long deploy_start;
    } // namespace ir
    namespace motor {
        extern bool spinning_up;
        extern bool spin_down;
        extern bool controller_on;
        extern int pulse_width;

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
        extern char const *log_filename;
    }

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