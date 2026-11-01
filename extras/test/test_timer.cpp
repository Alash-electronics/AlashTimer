// Тесты AlashTimer и AlashBlinker без железа:
//   g++ -std=c++17 -Wall -I mock -I ../../src test_timer.cpp ../../src/AlashTimer.cpp && ./a.out
#include <stdio.h>
#include "Arduino.h"
#include "AlashTimer.h"

static int fails = 0;
#define CHECK(cond) do { if (!(cond)) { printf("FAIL line %d: %s\n", __LINE__, #cond); fails++; } } while (0)

static int ticks = 0;
static void tick() { ticks++; }
// Прокручиваем время по 1 мс и считаем срабатывания
static int run(AlashTimer &t, uint32_t ms) { int n = 0; for (uint32_t i = 0; i < ms; i++) { g_ms++; if (t.ready()) n++; } return n; }
static void runLed(AlashBlinker &b, uint32_t ms, uint8_t log[], int &len) { for (uint32_t i = 0; i < ms; i++) { g_ms++; b.update(); log[len++] = g_pin[13]; } }

int main() {
  // 1) периодический: раз в 100 мс, без накопления ошибки
  g_ms = 1000;
  AlashTimer t(100);
  CHECK(run(t, 1000) == 10);
  CHECK(t.count() == 10);

  // 2) один раз
  AlashTimer o(500, AlashTimer::ONCE);
  CHECK(run(o, 2000) == 1 && !o.isRunning());
  o.start(); CHECK(run(o, 600) == 1);

  // 3) пропущенные срабатывания не повторяются, фаза сохраняется
  AlashTimer m(100);
  g_ms += 350;                                          // программа была занята 350 мс
  CHECK(m.ready() && !m.ready());
  CHECK(m.missed() == 2);
  g_ms += 50;                                           // 400 мс от старта: ровно следующая граница
  CHECK(m.ready());

  // 4) переполнение millis()
  g_ms = 0xFFFFFFFFu - 250;
  AlashTimer w(100);
  CHECK(run(w, 1000) == 10);

  // 5) пауза и продолжение
  g_ms = 5000;
  AlashTimer p(1000);
  g_ms += 400; p.pause();
  g_ms += 5000; CHECK(!p.ready());
  p.resume();
  CHECK(p.remaining() == 600);
  g_ms += 599; CHECK(!p.ready());
  g_ms += 1;   CHECK(p.ready());

  // 6) elapsed, remaining, progress, setInterval, stop
  AlashTimer q(1000);
  g_ms += 250;
  CHECK(q.elapsed() == 250 && q.remaining() == 750 && q.progress() > 0.249f && q.progress() < 0.251f);
  q.setInterval(200); CHECK(q.ready());
  q.stop(); g_ms += 5000; CHECK(!q.ready() && q.elapsed() == 0);

  // 7) обработчик
  AlashTimer h(10);
  h.onTick(tick);
  for (int i = 0; i < 100; i++) { g_ms++; h.update(); }
  CHECK(ticks == 10);

  // 8) микросекунды
  g_us = 0;
  AlashTimer u(500);
  u.setMicros(true); u.start();
  g_us = 499; CHECK(!u.ready());
  g_us = 500; CHECK(u.ready());

  // 9) мигание: 100 мс включено, 300 мс выключено
  g_ms = 10000;
  AlashBlinker led(13);
  led.begin();
  led.blink(100, 300);
  uint8_t log[5000]; int len = 0;
  runLed(led, 1600, log, len);
  int highs = 0, rises = 0;
  for (int i = 0; i < len; i++) { highs += log[i]; if (i && log[i] && !log[i - 1]) rises++; }
  CHECK(highs >= 395 && highs <= 405);                  // 4 периода по 100 мс
  CHECK(rises == 3 || rises == 4);

  // 10) flash: три вспышки и тишина
  AlashBlinker f(13);
  f.flash(3, 50, 50);
  len = 0; runLed(f, 600, log, len);
  rises = 0; highs = 0;
  for (int i = 0; i < len; i++) { highs += log[i]; if (i && log[i] && !log[i - 1]) rises++; }
  CHECK(rises == 2 && highs >= 148 && highs <= 152);    // первая вспышка стартует сразу + 2 подъёма
  CHECK(!f.isBusy() && !f.isOn() && g_pin[13] == 0);

  // 11) шаблон SOS: короткие, длинные, короткие; без повтора заканчивается
  static const uint16_t sos[] = {100, 100, 100, 100, 100, 300, 300, 100, 300, 100, 300, 300, 100, 100, 100, 100, 100, 700};
  AlashBlinker s(13);
  s.pattern(sos, 18, false);
  len = 0; runLed(s, 3800, log, len);
  highs = 0; for (int i = 0; i < len; i++) highs += log[i];
  CHECK(highs >= 1495 && highs <= 1505);                // 3*100 + 3*300 + 3*100 = 1500
  CHECK(!s.isBusy());

  // 12) активный LOW, on/off/toggle
  AlashBlinker a(13, true);
  a.begin(); CHECK(g_pin[13] == HIGH);                  // выключено = HIGH
  a.on();  CHECK(g_pin[13] == LOW && a.isOn());
  a.toggle(); CHECK(g_pin[13] == HIGH && !a.isOn());

  if (fails) { printf("FAILED: %d\n", fails); return 1; }
  printf("ALL TESTS PASSED\n");
  return 0;
}
