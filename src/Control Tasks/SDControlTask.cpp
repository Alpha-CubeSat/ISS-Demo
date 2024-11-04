#include "SDControlTask.hpp"
#include "constants.hpp"
#include "sfr.hpp"

#include <SPI.h>

const size_t bufferSize = 128;
char buffer[bufferSize];

volatile bool transfer_complete = false;

void dmaCallback(Adafruit_ZeroDMA *dma) {
    transfer_complete = true;
}

void SDControlTask::begin() {
    if (!SD.begin(SD_PIN, SD_SCK_MHZ(12))) {
        vlogln("Error: SD interface failed to initialize");
    }

    dma.allocate();
    dma.setTrigger(SERCOM4_DMAC_ID_TX);
    dma.setAction(DMA_TRIGGER_ACTON_BEAT);
    dma.setCallback(dmaCallback);

    desc = dma.addDescriptor(
        buffer,
        (void*)(&SERCOM4->SPI.DATA.reg),
        bufferSize,
        DMA_BEAT_SIZE_BYTE,
        true,
        false
    );
}

void SDControlTask::execute() {
    uint32_t start = millis();

    file = SD.open(constants::sd::filename, O_CREAT | O_WRITE | O_APPEND);
    if (!file) {
        Serial.println("Error: Could not open file");
    }

    snprintf(buffer, sizeof(buffer), "%lu,%d,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f\n", millis(), sfr::motor::pulse_width_angle, sfr::imu::accel_x, sfr::imu::accel_y, sfr::imu::accel_z, sfr::imu::gyro_x, sfr::imu::gyro_y, sfr::imu::gyro_z);


    transfer_complete = false;

    dma.startJob();

    while (!transfer_complete) {}

    if (file.write(buffer, bufferSize) != bufferSize) {
        Serial.println("Error: Failed to write data to SD card");
    }

    file.flush();
    file.close();
    uint32_t elapsed = millis() - start;
    Serial.print("SD DMA: ");
    Serial.println(elapsed);
}