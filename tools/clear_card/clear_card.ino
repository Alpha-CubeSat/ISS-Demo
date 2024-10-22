#include <Arduino.h>
#include <SD.h>

#define SD_PIN 4

void setup() {
    Serial.begin(9600);

    while (!Serial);

    if (!SD.begin(SD_PIN)) {
        while (true) {
            Serial.println("Error: SD interface failed to initialize");
        }
    }

    File root = SD.open("/");
    if (root) {
        while (true) {
            File entry = root.openNextFile();
            Serial.print("Deleting ");
            Serial.println(entry.name());

            if (!entry) {
                break;
            }

            if (!SD.remove(entry.name())) {
                Serial.print("Error: Could not delete ");
                Serial.print(entry.name());
            }
        }
        root.close();
    } else {
        Serial.println("Error: Opening root failed");
    }
}

void loop() {

}