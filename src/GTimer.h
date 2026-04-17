#pragma once
#include "GTMacro.h"
#include "GTimerCbT.h"
#include "GTimerT.h"
#include "uTimerT.h"

// ============= uTimer =============
template <unsigned long (*uptime)()>
using uTimer8 = uTimerT<uptime, uint8_t>;

template <unsigned long (*uptime)()>
using uTimer16 = uTimerT<uptime, uint16_t>;

template <unsigned long (*uptime)()>
using uTimer32 = uTimerT<uptime, uint32_t>;

template <unsigned long (*uptime)()>
using uTimer = uTimer32<uptime>;

// ============= GTimer =============
template <unsigned long (*uptime)()>
using GTimer8 = GTimerT<uptime, uint8_t>;

template <unsigned long (*uptime)()>
using GTimer16 = GTimerT<uptime, uint16_t>;

template <unsigned long (*uptime)()>
using GTimer32 = GTimerT<uptime, uint32_t>;

template <unsigned long (*uptime)()>
using GTimer = GTimer32<uptime>;

// ============= GTimerCb =============
template <unsigned long (*uptime)()>
using GTimerCb8 = GTimerCbT<uptime, uint8_t>;

template <unsigned long (*uptime)()>
using GTimerCb16 = GTimerCbT<uptime, uint16_t>;

template <unsigned long (*uptime)()>
using GTimerCb32 = GTimerCbT<uptime, uint32_t>;

template <unsigned long (*uptime)()>
using GTimerCb = GTimerCb32<uptime>;
