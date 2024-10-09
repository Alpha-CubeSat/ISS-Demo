#ifndef SFR_HPP
#define SFR_HPP

namespace sfr {
    namespace ir {
        extern bool is_armed;
        extern unsigned long armed_start;

        extern bool is_deploying;
        extern unsigned long deploy_start;
    } // namespace ir
    namespace motor {
        extern bool spinning_up;
        extern bool spin_down;
        extern bool controller_on; 
        extern int pulse_width;
        
    }

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
        extern char const *filename;
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
    }
}


#endif