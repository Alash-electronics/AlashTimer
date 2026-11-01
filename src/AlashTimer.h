// AlashTimer: таймеры без delay(): «раз в секунду», «через 5 секунд один раз», секундомер и мигающий светодиод по шаблону.
// Без зависимостей, безопасно через переполнение millis() (49 суток). MIT License. Alash Electronics.
#ifndef ALASH_TIMER_H
#define ALASH_TIMER_H

#include <Arduino.h>

class AlashTimer {
 public:
  enum Mode : uint8_t { PERIODIC = 0, ONCE = 1 };

  // intervalMs: период. PERIODIC: ready() даёт true раз в период; ONCE: один раз через период. autoStart: сразу запустить.
  explicit AlashTimer(uint32_t intervalMs = 1000, Mode mode = PERIODIC, bool autoStart = true);

  bool ready();                            // пора? (true один раз за период, без накопления ошибки)
  void start();                            // запустить с нуля
  void stop();                             // остановить
  void restart() { start(); }
  void pause();                            // приостановить, сохранив прошедшее время
  void resume();                           // продолжить с того же места
  void setInterval(uint32_t intervalMs) { _interval = intervalMs ? intervalMs : 1; }
  void setMode(Mode mode) { _mode = mode; }
  void setMicros(bool on) { _micros = on; }   // считать в микросекундах (интервал тоже в мкс)

  bool isRunning() const { return _running; }
  uint32_t elapsed();                      // сколько прошло в текущем периоде
  uint32_t remaining();                    // сколько осталось до срабатывания
  float progress();                        // 0..1 доля периода
  uint32_t count() const { return _count; }       // сколько раз сработал
  uint32_t missed() const { return _missed; }     // сколько срабатываний пропущено при последнем ready() (программа была занята)
  uint32_t interval() const { return _interval; }

  // Обработчик по желанию: update() вызывает его, когда пора
  void onTick(void (*fn)()) { _fn = fn; }
  void update() { if (ready() && _fn) _fn(); }

 private:
  uint32_t _interval;
  Mode _mode;
  bool _running = false, _micros = false;
  uint32_t _start = 0, _pausedAt = 0;
  uint32_t _count = 0, _missed = 0;
  void (*_fn)() = nullptr;
  uint32_t now() const { return _micros ? micros() : millis(); }
};

// Мигающий светодиод (или любой выход) без delay(): AlashBlinker led(13); led.blink(200, 800); и led.update() в loop().
class AlashBlinker {
 public:
  explicit AlashBlinker(uint8_t pin, bool activeLow = false) : _pin(pin), _low(activeLow) {}

  void begin();                            // настроить пин (вызывается сама при первом использовании)
  void on();                               // включить насовсем
  void off();                              // выключить насовсем
  void toggle();
  void blink(uint16_t onMs, uint16_t offMs);        // мигать бесконечно
  void flash(uint8_t times, uint16_t onMs = 150, uint16_t offMs = 150);   // мигнуть N раз и замолчать
  void pattern(const uint16_t *durationsMs, uint8_t count, bool repeat = true);   // свой шаблон: включено, выключено, включено...
  void stop() { off(); }
  bool isOn() const { return _state; }
  bool isBusy() const { return _mode != IDLE; }    // идёт мигание
  void update();                           // вызывайте в loop()

 private:
  enum RunMode : uint8_t { IDLE, BLINK, FLASH, PATTERN } _mode = IDLE;
  uint8_t _pin;
  bool _low, _started = false, _state = false, _repeat = false;
  uint16_t _on = 0, _off = 0;
  uint8_t _left = 0, _idx = 0, _n = 0;
  const uint16_t *_pat = nullptr;
  uint32_t _since = 0;
  void write(bool on);
};

#endif  // ALASH_TIMER_H
