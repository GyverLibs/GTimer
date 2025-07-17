#pragma once
#include "GTimerT.h"

#ifndef __AVR__
#include <functional>
#endif

// ============= GTimerCbT =============
template <unsigned long (*uptime)(), typename T>
class GTimerCbT : public GTimerT<uptime, T> {
#ifdef __AVR__
    typedef void (*TimerCallback)();
#else
    typedef std::function<void()> TimerCallback;
#endif

   public:
    using GTimerT<uptime, T>::GTimerT;

    GTimerCbT(uint32_t time, TimerCallback cb, GTMode mode = GTMode::Interval, bool keepPhase = false) : GTimerT<uptime, T>(time, true, mode, keepPhase), _cb(cb) {}

    // подключить обработчик таймера
    void attach(TimerCallback cb) {
        _cb = cb;
    }

    // отключить обработчик таймера
    void detach() {
        _cb = nullptr;
    }

    // запустить в режиме таймаута
    void startTimeout(uint32_t time, TimerCallback cb) {
        start(time, GTMode::Timeout);
        attach(cb);
    }

    // запустить в режиме интервала
    void startInterval(uint32_t time, TimerCallback cb) {
        start(time, GTMode::Interval);
        attach(cb);
    }

    // запустить в режиме переполнения
    void startOverflow(uint32_t time, TimerCallback cb) {
        start(time, GTMode::Overflow);
        attach(cb);
    }

    // тикер, вызывать в loop. Вернёт true при срабатывании
    bool tick() {
        if (GTimerT<uptime, T>::tick()) {
            onReady();
            if (_cb) {
                thisGTimer = this;
                _cb();
            }
            return true;
        }
        return false;
    }

    using GTimerT<uptime, T>::start;

   protected:
    // вызывается при срабатывании
    virtual void onReady() {}

   private:
    TimerCallback _cb = nullptr;
};