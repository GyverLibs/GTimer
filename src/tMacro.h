#pragma once
#include <inttypes.h>

#define EVERY_T(prd, uptime, T) if (static T _tmr_ = 0; T(T(uptime()) - _tmr_) >= (prd) ? (_tmr_ = uptime(), true) : false)

#define EVERY_S(s) EVERY_T(s * 1000ul, millis, uint32_t)

#define EVERY_MS(ms) EVERY_T(ms, millis, uint32_t)
#define EVERY16_MS(ms) EVERY_T(ms, millis, uint16_t)
#define EVERY8_MS(ms) EVERY_T(ms, millis, uint8_t)

#define EVERY_US(us) EVERY_T(us, micros, uint32_t)
#define EVERY16_US(us) EVERY_T(us, micros, uint16_t)
#define EVERY8_US(us) EVERY_T(us, micros, uint8_t)

#define PHASE_T(prd, uptime, T) if (static T _tmr_ = 0; T(T(uptime()) - _tmr_) >= (prd) ? (_tmr_ += prd, true) : false)

#define PHASE_S(s) PHASE_T(s * 1000ul, millis, uint32_t)

#define PHASE_MS(ms) PHASE_T(ms, millis, uint32_t)
#define PHASE16_MS(ms) PHASE_T(ms, millis, uint16_t)
#define PHASE8_MS(ms) PHASE_T(ms, millis, uint8_t)

#define PHASE_US(us) PHASE_T(us, micros, uint32_t)
#define PHASE16_US(us) PHASE_T(us, micros, uint16_t)
#define PHASE8_US(us) PHASE_T(us, micros, uint8_t)
