// Basic demo for accelerometer/gyro readings from Adafruit LSM6DS3TR-C

#include <Arduino.h>
#include <Adafruit_LSM6DS3TRC.h>
#include <SPI.h>
#include <SD.h>
#include <time.h>
#include <stdio.h>

// For SPI mode, we need a CS pin
#define LSM_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define LSM_SCK 13
#define LSM_MISO 12
#define LSM_MOSI 11

Adafruit_LSM6DS3TRC lsm6ds3trc;
File myFile;
File logFile;
time_t t;

void setup(void) {
  Serial.begin(115200);

  while (!Serial)
    delay(10);

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("Initialization Failed!");
    while (1);
  }
  Serial.println("Initialization Done!");

  time_t t;
  time(&t);
  char *myTime = ctime(&t);
  char *extension = ".txt";
  char str[255];
  String logFileName = strcat(myTime, extension);
  File logFile = SD.open(logFileName, FILE_WRITE);


  if (!lsm6ds3trc.begin_I2C()) {
    logFile.println("Failed to find IMU chip!");
    while (1) {
      delay(10);
    }
  }

  logFile.print(ctime(&t));
  logFile.print(": ");
  logFile.println("IMU Found!");

  logFile.print(ctime(&t));
  logFile.print(": ");
  logFile.print("Accelerometer range set to: ");
  switch (lsm6ds3trc.getAccelRange()) {
  case LSM6DS_ACCEL_RANGE_2_G:
    logFile.println("+-2G");
    break;
  case LSM6DS_ACCEL_RANGE_4_G:
    logFile.println("+-4G");
    break;
  case LSM6DS_ACCEL_RANGE_8_G:
    logFile.println("+-8G");
    break;
  case LSM6DS_ACCEL_RANGE_16_G:
    logFile.println("+-16G");
    break;
  }

  // lsm6ds3trc.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS);
  logFile.print(ctime(&t));
  logFile.print(": ");
  logFile.print("Gyro range set to: ");
  switch (lsm6ds3trc.getGyroRange()) {
  case LSM6DS_GYRO_RANGE_125_DPS:
    logFile.println("125 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_250_DPS:
    logFile.println("250 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_500_DPS:
    logFile.println("500 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_1000_DPS:
    logFile.println("1000 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_2000_DPS:
    logFile.println("2000 degrees/s");
    break;
  case ISM330DHCX_GYRO_RANGE_4000_DPS:
    break; // unsupported range for the DS33
  }

  // lsm6ds3trc.setAccelDataRate(LSM6DS_RATE_12_5_HZ);
  logFile.print(ctime(&t));
  logFile.print(": ");
  logFile.print("Accelerometer data rate to: ");
  switch (lsm6ds3trc.getAccelDataRate()) {
  case LSM6DS_RATE_SHUTDOWN:
    logFile.println("0 Hz");
    break;
  case LSM6DS_RATE_12_5_HZ:
    logFile.println("12.5 Hz");
    break;
  case LSM6DS_RATE_26_HZ:
    logFile.println("26 Hz");
    break;
  case LSM6DS_RATE_52_HZ:
    logFile.println("52 Hz");
    break;
  case LSM6DS_RATE_104_HZ:
    logFile.println("104 Hz");
    break;
  case LSM6DS_RATE_208_HZ:
    logFile.println("208 Hz");
    break;
  case LSM6DS_RATE_416_HZ:
    logFile.println("416 Hz");
    break;
  case LSM6DS_RATE_833_HZ:
    logFile.println("833 Hz");
    break;
  case LSM6DS_RATE_1_66K_HZ:
    logFile.println("1.66 KHz");
    break;
  case LSM6DS_RATE_3_33K_HZ:
    logFile.println("3.33 KHz");
    break;
  case LSM6DS_RATE_6_66K_HZ:
    logFile.println("6.66 KHz");
    break;
  }

  // lsm6ds3trc.setGyroDataRate(LSM6DS_RATE_12_5_HZ);
  logFile.print(ctime(&t));
  logFile.print(": ");
  logFile.print("Gyro data rate set to: ");
  switch (lsm6ds3trc.getGyroDataRate()) {
  case LSM6DS_RATE_SHUTDOWN:
    logFile.println("0 Hz");
    break;
  case LSM6DS_RATE_12_5_HZ:
    logFile.println("12.5 Hz");
    break;
  case LSM6DS_RATE_26_HZ:
    logFile.println("26 Hz");
    break;
  case LSM6DS_RATE_52_HZ:
    logFile.println("52 Hz");
    break;
  case LSM6DS_RATE_104_HZ:
    logFile.println("104 Hz");
    break;
  case LSM6DS_RATE_208_HZ:
    logFile.println("208 Hz");
    break;
  case LSM6DS_RATE_416_HZ:
    logFile.println("416 Hz");
    break;
  case LSM6DS_RATE_833_HZ:
    logFile.println("833 Hz");
    break;
  case LSM6DS_RATE_1_66K_HZ:
    logFile.println("1.66 KHz");
    break;
  case LSM6DS_RATE_3_33K_HZ:
    logFile.println("3.33 KHz");
    break;
  case LSM6DS_RATE_6_66K_HZ:
    logFile.println("6.66 KHz");
    break;
  }

  lsm6ds3trc.configInt1(false, false, true); // accelerometer DRDY on INT1
  lsm6ds3trc.configInt2(false, true, false); // gyro DRDY on INT2

  myFile = SD.open("test.csv", FILE_WRITE);

  myFile.println("Accel X, Accel Y, Accel Z");
  myFile.flush();
}
 
void loop() {
  // Get a new normalized sensor event
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  //lsm6ds3trc.getEvent(&accel, &gyro, &temp);

  SD.remove("TEST2.csv");
  myFile = SD.open("TEST2.csv", FILE_WRITE);

  myFile.println("Time (s), Accel X (m/s^2), Accel Y (m/s^2), Accel Z (m/s)^2, Gyro X (rad/sec), Gyro Y (rad/sec), Gyro Z (rad/sec)");
  myFile.flush();

  float current_time = millis();

  for(int i = 0; i < 1000; i++)
  {
    float this_time = millis();
    float dt = (this_time - current_time) / 1000;
    lsm6ds3trc.getEvent(&accel, &gyro, &temp);

    if (myFile) {
    
    myFile.print(dt);
    myFile.print(", ");
    myFile.print(accel.acceleration.x);
    myFile.print(", ");
    myFile.print(accel.acceleration.y);
    myFile.print(", ");
    myFile.print(accel.acceleration.z);
    myFile.print(", ");
    myFile.print(gyro.gyro.x);
    myFile.print(", ");
    myFile.print(gyro.gyro.y);
    myFile.print(", ");
    myFile.println(gyro.gyro.z);
    myFile.flush();

  } else {
    // if the file didn't open, print an error:
    logFile.print(ctime(&t));
    logFile.print(": ");
    logFile.println("Error opening data file; exiting...");
    exit(0);
  }

  }
  // close the file:
    myFile.close();
    Serial.println("complete!");

}
