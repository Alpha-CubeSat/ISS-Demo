#include "IMUMonitor.hpp"

#include "sfr.hpp"
#include "constants.hpp"

void IMUMonitor::begin() {
    if (imu.begin_I2C()) {
        imu.setGyroDataRate(LSM6DS_RATE_208_HZ);
        imu.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS);
        imu.setAccelDataRate(LSM6DS_RATE_208_HZ);
        imu.setAccelRange(LSM6DS_ACCEL_RANGE_4_G);
    } else {
        sfr::imu::failed_init = true;
        vlogln("Error: IMU failed to initialize");
    }
}

void IMUMonitor::execute() {
    if (imu.getEvent(&accel, &gyro, &temp)) {
        sfr::imu::accel_x = accel.acceleration.x;
        sfr::imu::accel_y = accel.acceleration.y;
        sfr::imu::accel_z = accel.acceleration.z;

        sfr::imu::gyro_x = gyro.gyro.x;
        sfr::imu::gyro_y = gyro.gyro.y;
        sfr::imu::gyro_z = gyro.gyro.z;
    } else {
        vlogln("Error: IMU failed to read");
        // TODO: Log this failure.
    }
}