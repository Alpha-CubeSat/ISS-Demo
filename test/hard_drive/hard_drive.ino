#include <Arduino.h>
#include <Servo.h>

#define PWM_PIN 10

Servo esc;

void setup() {
    Serial.begin(9600);
    esc.attach(PWM_PIN, 1000, 2000);
    esc.write(0);
}

void loop() {
    esc.write(100);
    delay(10_000);
    esc.write(0);
}