#pragma once
#include "GTimerCbT.h"
#include "GTimerT.h"
#include "GTMacro.h"
#include "uTimerT.h"

// ============= uTimer =============
template <unsigned long (*uptime)()>
using uTimer8 = uTimerT<uptime, uint8_t>;

template <unsigned long (*uptime)()>
using uTimer16 = uTimerT<uptime, uint16_t>;

template <unsigned long (*uptime)()>
using uTimer = uTimerT<uptime, uint32_t>;

// ============= GTimer =============
template <unsigned long (*uptime)()>
using GTimer8 = GTimerT<uptime, uint8_t>;

template <unsigned long (*uptime)()>
using GTimer16 = GTimerT<uptime, uint16_t>;

template <unsigned long (*uptime)()>
using GTimer = GTimerT<uptime, uint32_t>;

// ============= GTimerCb =============
template <unsigned long (*uptime)()>
using GTimerCb8 = GTimerCbT<uptime, uint8_t>;

template <unsigned long (*uptime)()>
using GTimerCb16 = GTimerCbT<uptime, uint16_t>;

template <unsigned long (*uptime)()>
using GTimerCb = GTimerCbT<uptime, uint32_t>;
