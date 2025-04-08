#pragma once
#include <inttypes.h>

#ifndef __AVR__
#include <functional>
#endif

enum class GTMode : uint8_t {
    Interval,  // перезапускается при срабатывании
    Timeout,   // останавливается при срабатывании
    Overflow,  // продолжает срабатывать при срабатывании
};

static void* thisGTimer = nullptr;

#define _GT_INTERVAL 0
#define _GT_TIMEOUT 1
#define _GT_OVERFLOW 2
#define _GT_STOPPED 0
#define _GT_RUNNING 1
#define _GT_PAUSED 2

// ============= GTimerT =============
template <unsigned long (*uptime)(), typename T>
class GTimerT {
   public:
    GTimerT() {}
    GTimerT(uint32_t time, bool start = false, GTMode mode = GTMode::Interval, bool keepPhase = false) : _prd(time), _phase(keepPhase) {
        setMode(mode);
        if (start) GTimerT::start();
    }

    // держать фазу в режиме Interval (умолч. false)
    void keepPhase(bool keep) {
        _phase = keep;
    }

    // держать фазу в режиме Interval
    bool getPhase() {
        return _phase;
    }

    // установить время в единицах таймера
    void setTime(uint32_t time) {
        _prd = time;
        _overflow = false;
    }

    // установить время (для мс)
    void setTime(uint32_t ms, uint32_t sec, uint16_t min = 0, uint16_t hour = 0, uint16_t day = 0) {
        if (sec) ms += sec * 1000ul;
        if (min) ms += min * 60 * 1000ul;
        if (hour) ms += hour * 60 * 60 * 1000ul;
        if (day) ms += day * 24 * 60 * 60 * 1000ul;
        setTime(ms);
    }

    // получить время в единицах таймера
    T getTime() {
        return _prd;
    }

    // установить режим: GTMode::Interval, GTMode::Timeout, GTMode::Overflow
    void setMode(GTMode mode) {
        _mode = (uint8_t)mode;
        _overflow = false;
    }

    // получить режим: GTMode::Interval, GTMode::Timeout, GTMode::Overflow
    GTMode getMode() {
        return (GTMode)_mode;
    }

    // запустить с указанием времени (для мс)
    void start(uint32_t ms, uint32_t sec, uint16_t min = 0, uint16_t hour = 0, uint16_t day = 0) {
        setTime(ms, sec, min, hour, day);
        start();
    }

    // запустить с указанием времени и режима
    void start(uint32_t time, GTMode mode) {
        setMode(mode);
        start(time);
    }

    // запустить с указанием времени
    void start(uint32_t time) {
        setTime(time);
        start();
    }

    // запустить/перезапустить
    void start() {
        _tmr = uptime();
        _state = _GT_RUNNING;
        _overflow = false;
    }

    // приостановить
    void pause() {
        if (_state == _GT_RUNNING) {
            _state = _GT_PAUSED;
            _tmr = (T)uptime() - _tmr;
        }
    }

    // продолжить
    void resume() {
        if (_state == _GT_PAUSED) {
            _state = _GT_RUNNING;
            _tmr = (T)uptime() - _tmr;
        }
    }

    // остановить
    void stop() {
        _state = _GT_STOPPED;
        _overflow = false;
    }

    // вызвать срабатывание
    void force() {
        if (running()) _tmr = (T)uptime() - _prd;
    }

    // таймер запущен
    inline bool running() {
        return _state == _GT_RUNNING;
    }

    // прошло времени в единицах таймера
    T getCurrent() {
        if (_overflow) return 0;
        switch (_state) {
            case _GT_RUNNING: return (T)uptime() - _tmr;
            case _GT_PAUSED: return _tmr;
        }
        return 0;
    }

    // осталось времени в единицах таймера
    T getLeft() {
        if (_overflow) return 0;
        T t = getCurrent();
        return (_prd >= t) ? (_prd - t) : 0;
    }

    // осталось времени в 8 бит (0.. 255)
    uint8_t getLeft8() {
        return _prd ? (getLeft() * 255ull / _prd) : 0;
    }

    // осталось времени в 16 бит (0.. 65 535)
    uint16_t getLeft16() {
        return _prd ? (getLeft() * 65535ull / _prd) : 0;
    }

    // тикер, вызывать в loop. Вернёт true при срабатывании
    bool tick() {
        if (running() && (_overflow || (T)((T)uptime() - _tmr) >= _prd)) {
            switch (_mode) {
                case _GT_INTERVAL:
                    if (_phase) {
                        T left = (T)((T)uptime() - _tmr);
                        _tmr += _prd * ((left >= _prd * 2) ? (left / _prd) : 1);
                    } else {
                        _tmr = uptime();
                    }
                    break;
                case _GT_TIMEOUT:
                    stop();
                    break;
                case _GT_OVERFLOW:
                    _overflow = true;
                    break;
            }
            return true;
        }
        return false;
    }

    // вызов tick
    operator bool() {
        return tick();
    }

   private:
    T _tmr, _prd;

    uint8_t _mode : 2;
    uint8_t _state : 2;
    uint8_t _phase : 1;
    uint8_t _overflow : 1;
};

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

// ============= GTimer =============
template <unsigned long (*uptime)()>
class GTimer8 : public GTimerT<uptime, uint8_t> {
   public:
    using GTimerT<uptime, uint8_t>::GTimerT;
};

template <unsigned long (*uptime)()>
class GTimer16 : public GTimerT<uptime, uint16_t> {
   public:
    using GTimerT<uptime, uint16_t>::GTimerT;
};

template <unsigned long (*uptime)()>
class GTimer : public GTimerT<uptime, uint32_t> {
   public:
    using GTimerT<uptime, uint32_t>::GTimerT;
};

// ============= GTimerCb =============
template <unsigned long (*uptime)()>
class GTimerCb8 : public GTimerCbT<uptime, uint8_t> {
   public:
    using GTimerCbT<uptime, uint8_t>::GTimerCbT;
};

template <unsigned long (*uptime)()>
class GTimerCb16 : public GTimerCbT<uptime, uint16_t> {
   public:
    using GTimerCbT<uptime, uint16_t>::GTimerCbT;
};

template <unsigned long (*uptime)()>
class GTimerCb : public GTimerCbT<uptime, uint32_t> {
   public:
    using GTimerCbT<uptime, uint32_t>::GTimerCbT;
};

// ============= MACRO =============
// #define EVERY_T(prd, uptime) if (static uint32_t _tmr_ = 0; !(uptime() - _tmr_ >= (prd) ? (_tmr_ = uptime(), true) : false)); else
#define EVERY_T(prd, uptime) if (static uint32_t _tmr_ = 0; uptime() - _tmr_ >= (prd) ? (_tmr_ = uptime(), true) : false)
#define EVERY_MS(ms) EVERY_T(ms, millis)
#define EVERY_US(us) EVERY_T(us, micros)
