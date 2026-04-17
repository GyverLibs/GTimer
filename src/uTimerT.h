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
    bool interval(T prd) {
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
    bool overflow(T prd) const {
        return _tmr && elapsed() >= prd;
    }

    // прошло времени со старта
    T elapsed() const {
        return T(uptime()) - _tmr;
    }

    // таймер запущен
    bool running() const {
        return _tmr;
    }

    // таймер запущен
    operator bool() const {
        return _tmr;
    }

    // устарело
    bool period(T prd) { return interval(prd); }

   private:
    T _tmr = 0;
};