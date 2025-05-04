/**
 * @file IMUMonitor.cpp
 * @author csg83
 *
 * @brief Reads IMU data and updates the SFR
 */

#include "IMUMonitor.hpp"

#include "constants.hpp"
#include "sfr.hpp"

void IMUMonitor::begin() {
#ifdef AUTOMATED_SEQUENCE_NO_IMU
    if (sfr::mission::mode->get_id() == 7) {
        return;
    }
#endif

    if (imu.begin_I2C()) {
        imu.setGyroDataRate(LSM6DS_RATE_208_HZ);
        imu.setGyroRange(LSM6DS_GYRO_RANGE_1000_DPS);
        imu.setAccelDataRate(LSM6DS_RATE_208_HZ);
        imu.setAccelRange(LSM6DS_ACCEL_RANGE_4_G);

        sfr::imu::failed_init = false;
    } else {
        sfr::mission::events.enqueue(Event::imu_init_failure);
        sfr::imu::failed_init = true;
    }
}

void IMUMonitor::execute() {
#ifdef AUTOMATED_SEQUENCE_NO_IMU
    if (sfr::mission::mode->get_id() == 7) {
        return;
    }
#endif

    if (sfr::imu::failed_init) {
        return;
    }

    // Reset failed read indicator
    if (sfr::imu::failed_read) {
        sfr::imu::failed_read = false;
    }

    if (imu.getEvent(&accel, &gyro, &temp)) {
        sfr::imu::accel_x = accel.acceleration.x;
        sfr::imu::accel_y = accel.acceleration.y;
        sfr::imu::accel_z = accel.acceleration.z;

        sfr::imu::gyro_x = gyro.gyro.x;
        sfr::imu::gyro_y = gyro.gyro.y;
        sfr::imu::gyro_z = gyro.gyro.z;
    } else {
        sfr::mission::events.enqueue(Event::imu_read_failure);
        sfr::imu::failed_read = true;
    }
}