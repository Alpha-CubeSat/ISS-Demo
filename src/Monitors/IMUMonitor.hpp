#ifndef IMU_MONITOR_HPP
#define IMU_MONITOR_HPP

#include <Adafruit_LSM6DS3TRC.h>


class IMUMonitor {
public:
    IMUMonitor();

    void execute();

private:
    Adafruit_LSM6DS3TRC imu;

};

#endif