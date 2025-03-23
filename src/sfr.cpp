/**
 * @file sfr.cpp
 * @author csg83, vsc32
 *
 * @brief State field registry for global state management
 */

#include "sfr.hpp"

namespace sfr {
    namespace mission {
        InitialSpinupMode initial_spinup_class;
        StandbyMode standby_class;
        ArmedMode armed_class;
        DeploymentMode deployment_class;
        DespinMode despin_class;
        ControllerSpinupMode controller_spinup_class;
        OpenLoopMode open_loop_class;
        AutomatedSequenceMode automated_sequence_class;

        MissionMode *initial_spinup = &initial_spinup_class;
        MissionMode *standby = &standby_class;
        MissionMode *armed = &armed_class;
        MissionMode *deployment = &deployment_class;
        MissionMode *despin = &despin_class;
        MissionMode *controller_spinup = &controller_spinup_class;
        MissionMode *open_loop = &open_loop_class;
        MissionMode *automated_sequence = &automated_sequence_class;

        MissionMode *mode = &initial_spinup_class;

        uint32_t timestamp = 0;

        bool began_deployment = false;
        bool deployed = false;

        Queue events;

    } // namespace mission
    namespace ir {
        bool is_armed = false;
        bool was_invalid = false;

    } // namespace ir
    namespace motor {
        bool began_initial_spin = false;
        bool controller_on = false;

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
        bool failed_init = false;
        char const *log_filename = "data_0.csv";

    } // namespace sd

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
