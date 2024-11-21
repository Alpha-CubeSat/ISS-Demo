#include "sfr.hpp"

namespace sfr {
    namespace test {
        volatile bool automated = false;
    } // namespace test
    namespace ir {
        bool is_armed = false;
        unsigned long armed_start = 0;

        bool is_deploying = false;
        unsigned long deploy_start = 0;
    } // namespace ir
    namespace motor {
        bool spinning_up = false;
        bool spin_down = false;
        int pulse_width_angle = 100;
    } // namespace motor

    namespace imu {
        bool failed_init = false;

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
} // namespace sfr