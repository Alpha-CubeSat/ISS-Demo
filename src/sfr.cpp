#include "sfr.hpp"

namespace sfr {
    namespace mission {
        StandbyMode standby_class;
        ArmedMode armed_class;
        DeploymentMode deployment_class;
        DespinMode despin_class;
        ControllerSpinupMode controller_spinup_class;
        OpenLoopMode open_loop_class;

        MissionMode *standby = &standby_class;
        MissionMode *armed = &armed_class;
        MissionMode *deployment = &deployment_class;
        MissionMode *despin = &despin_class;
        MissionMode *controller_spinup = &controller_spinup_class;
        MissionMode *open_loop = &open_loop_class;

        MissionMode *mode = &standby_class;
    } // namespace mission
    namespace flight {
        bool initial_hold = true;
        bool initial_spin = false;
        volatile bool automated = false;
    } // namespace flight
    namespace ir {
        bool is_armed = false;
        unsigned long armed_start = 0;

        unsigned long deploy_start = 0;
    } // namespace ir
    namespace motor {
        bool spinning_up = false;
        bool spin_down = false;
        bool controller_on = false;
        int pulse_width = 0;
    } // namespace motor

    namespace imu {
        bool failed_init = false;
        bool failed_read = false;

        float accel_x = 0;
        float accel_y = 0;
        float accel_z = 0;

        float gyro_x = 0;
        float gyro_y = 0;
        float gyro_z = 0;
    } // namespace imu

    namespace sd {
        char const *log_filename = "data_0.csv";
    }

    namespace controller {
        float record_angle = 0;
        float record_duty_cycle = 0;
        float record_error = 0;
        float record_delta_error = 0;
        float record_delta_time = 0;
        float record_prop = 0;
        float record_derivative = 0;
        float record_integral = 0;

        bool record_data = false;
    } // namespace controller
} // namespace sfr
