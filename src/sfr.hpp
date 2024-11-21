#ifndef SFR_HPP
#define SFR_HPP

namespace sfr {
    namespace test {
        extern volatile bool automated;
    } // namespace test
    namespace ir {
        extern bool is_armed;
        extern unsigned long armed_start;

        extern bool is_deploying;
        extern unsigned long deploy_start;
    } // namespace ir
    namespace motor {
        extern bool spinning_up;
        extern bool spin_down;
        extern int pulse_width_angle;
    } // namespace motor

    namespace imu {
        extern bool failed_init;

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
} // namespace sfr

#endif