#include <Arduino.h>
#include <Servo.h>

#define BUTTON_PIN 5
#define GATE_PIN A4

Servo esc;
int val = 0;

void setup() {
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    digitalWrite(GATE_PIN, LOW);
}

void loop() {
    if (digitalRead(BUTTON_PIN) == 0) {
        Serial.println("button pressed");
        digitalWrite(GATE_PIN, HIGH);
        delay(1);
        digitalWrite(GATE_PIN, LOW);
    }
}
