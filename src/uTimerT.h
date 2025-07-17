#pragma once
#include <inttypes.h>

template <unsigned long (*uptime)(), typename T>
class uTimerT {
   public:
    uTimerT(bool start = false) {
        if (start) uTimerT::start();
    }

    // запустить/перезапустить
    void start() {
        _tmr = uptime();
        if (!_tmr) --_tmr;
    }

    // остановить
    void stop() {
        _tmr = 0;
    }

    // таймаут
    bool timeout(T tout) {
        if (overflow(tout)) {
            stop();
            return true;
        }
        return false;
    }

    // период
    bool period(T prd) {
        if (overflow(prd)) {
            start();
            return true;
        }
        return false;
    }

    // фаза
    bool phase(T prd) {
        if (overflow(prd)) {
            _tmr += prd;
            if (!_tmr) --_tmr;
            return true;
        }
        return false;
    }

    // переполнение
    bool overflow(T prd) {
        return _tmr && elapsed() >= prd;
    }

    // таймер запущен
    bool running() {
        return _tmr;
    }

    // прошло времени со старта
    T elapsed() {
        return T(uptime()) - _tmr;
    }

   private:
    T _tmr = 0;
};