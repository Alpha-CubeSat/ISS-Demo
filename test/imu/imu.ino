#include <Arduino.h>
#include <Adafruit_LSM6DS3TRC.h>

Adafruit_LSM6DS3TRC imu;

sensors_event_t accel;
sensors_event_t gyro;
sensors_event_t temp;

void setup() {
    if (imu.begin_I2C()) {
        imu.setGyroDataRate(LSM6DS_RATE_208_HZ);
        imu.setGyroRange(LSM6DS_GYRO_RANGE_1000_DPS);
        imu.setAccelDataRate(LSM6DS_RATE_208_HZ);
        imu.setAccelRange(LSM6DS_ACCEL_RANGE_4_G);
    } else {
        while (true) {
            Serial.println("Error: IMU failed to initialize");
            delay(1000);
        }
    }
}


void loop() {

    if (imu.getEvent(&accel, &gyro, &temp)) {
        Serial.print(F("Gyro X: "));
        Serial.println(gyro.gyro.x);

        Serial.print(F("Gyro Y: "));
        Serial.println(gyro.gyro.y);

        Serial.print(F("Gyro Z: "));
        Serial.println(gyro.gyro.z);

        Serial.print(F("Accel X: "));
        Serial.println(accel.acceleration.x);

        Serial.print(F("Accel Y: "));
        Serial.println(accel.acceleration.y);

        Serial.print(F("Accel Z: "));
        Serial.println(accel.acceleration.z);
    } else {
        Serial.println("Error: IMU failed to read");
    }
    delay(500);
}