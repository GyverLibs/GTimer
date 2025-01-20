#include <Arduino.h>
#include <GTimer.h>

GTimerCb<millis> tmr1, tmr2;

void onTimer() {
    Serial.println("ready 2");
}

void setup() {
    Serial.begin(115200);

    // лямбда
    tmr1.startInterval(500, []() {
        Serial.println("ready 1");

        // обращение к текущему таймеру
        // static_cast<GTimerCb<millis>*>(thisGTimer)->stop();
    });

    // внешний
    tmr2.startInterval(1000, onTimer);
}

void loop() {
    tmr1.tick();
    tmr2.tick();
}