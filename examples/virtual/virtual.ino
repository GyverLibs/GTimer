#include <Arduino.h>
#include <GTimer.h>

class TestTimer : public GTimerCb<millis> {
   public:
    using GTimerCb<millis>::GTimerCb;

    void onReady() {
        Serial.println("ready");
    }
};

TestTimer tmr(500, true);

void setup() {
    Serial.begin(115200);
}

void loop() {
    tmr.tick();
}