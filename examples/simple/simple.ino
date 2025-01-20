#include <Arduino.h>
#include <GTimer.h>

GTimer<millis> tmr1;

void setup() {
    Serial.begin(115200);

    tmr1.setMode(GTMode::Timeout);
    tmr1.setTime(2000);
    tmr1.start();
}

void loop() {
    if (tmr1) Serial.println("timeout");

    static GTimer<millis> tmr2(500, true);
    if (tmr2) Serial.println("interval");
}