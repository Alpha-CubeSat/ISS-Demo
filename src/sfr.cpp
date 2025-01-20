#include "sfr.hpp"

namespace sfr {
    namespace flight {
        bool initial_hold = true;
        bool initial_spin = false;
        volatile bool automated = false;
    } // namespace flight
    namespace ir {
        bool is_armed = false;
        unsigned long armed_start = 0;

        bool is_deploying = false;
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
