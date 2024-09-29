#ifndef IMU_MONITOR_HPP
#define IMU_MONITOR_HPP

#include <Adafruit_LSM6DS3TRC.h>


class IMUMonitor {
public:

    void begin();
    void execute();

private:
    Adafruit_LSM6DS3TRC imu;

    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;
};

#endif