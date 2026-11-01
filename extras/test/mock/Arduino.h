// Минимальная имитация Arduino.h для запуска тестов на компьютере (g++).
#pragma once
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define OUTPUT 1
#define LOW 0
#define HIGH 1
inline uint32_t g_ms = 1000;
inline uint32_t g_us = 0;
inline uint8_t g_pin[64];
inline int g_writes = 0;
inline uint32_t millis() { return g_ms; }
inline uint32_t micros() { return g_us; }
inline void pinMode(uint8_t, uint8_t) {}
inline void digitalWrite(uint8_t p, uint8_t v) { g_pin[p] = v; g_writes++; }
