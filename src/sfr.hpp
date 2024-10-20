#ifndef SFR_HPP
#define SFR_HPP

namespace sfr {
    namespace ir {
        extern bool is_armed;
        extern unsigned long armed_start;

        extern bool is_deploying;
        extern unsigned long deploy_start;
    }
    namespace motor {
        extern bool spinning_up;
        extern bool spin_down;
        extern int pulse_width_angle;
    }

    namespace imu {
        extern bool failed_init;

        extern float accel_x;
        extern float accel_y;
        extern float accel_z;

        extern float gyro_x;
        extern float gyro_y;
        extern float gyro_z;
    }
}


#endif