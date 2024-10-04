#include "sfr.hpp"

namespace sfr {
    namespace ir {
        bool is_armed = false;
    }
    namespace motor {
        bool spinning_up = false;
        bool spin_down = false;
        int pulse_width = 0;
    }
    
    namespace imu {
        bool failed_init = false;

        float accel_x = 0;
        float accel_y = 0;
        float accel_z = 0;

        float gyro_x = 0;
        float gyro_y = 0;
        float gyro_z = 0;
    }
}