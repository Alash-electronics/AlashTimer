// MIT License. Alash Electronics.
#include "AlashTimer.h"

AlashTimer::AlashTimer(uint32_t intervalMs, Mode mode, bool autoStart) : _interval(intervalMs ? intervalMs : 1), _mode(mode) {
  if (autoStart) start();
}

void AlashTimer::start() {
  _start = now();
  _running = true;
  _count = 0;
  _missed = 0;
}

void AlashTimer::stop() { _running = false; }

void AlashTimer::pause() {
  if (!_running) return;
  _pausedAt = now();
  _running = false;
}

void AlashTimer::resume() {
  if (_running || _pausedAt == 0) return;
  _start += now() - _pausedAt;             // время паузы не считается
  _pausedAt = 0;
  _running = true;
}

bool AlashTimer::ready() {
  if (!_running) return false;
  uint32_t el = now() - _start;            // беззнаковая разность корректна и при переполнении счётчика
  if (el < _interval) return false;
  uint32_t n = el / _interval;
  _missed = n - 1;
  _count++;
  if (_mode == ONCE) {
    _running = false;
  } else {
    _start += n * _interval;               // фаза сохраняется: ошибка не копится, пропущенные срабатывания не повторяются
  }
  return true;
}

uint32_t AlashTimer::elapsed() { return _running ? now() - _start : 0; }
uint32_t AlashTimer::remaining() {
  if (!_running) return 0;
  uint32_t el = now() - _start;
  return el >= _interval ? 0 : _interval - el;
}
float AlashTimer::progress() {
  if (!_running) return 0;
  uint32_t el = now() - _start;
  return el >= _interval ? 1.0f : (float)el / (float)_interval;
}

// ---- AlashBlinker ----------------------------------------------------------------------

void AlashBlinker::begin() {
  pinMode(_pin, OUTPUT);
  _started = true;
  write(false);
}

void AlashBlinker::write(bool on) {
  _state = on;
  digitalWrite(_pin, (on != _low) ? HIGH : LOW);
}

void AlashBlinker::on() { if (!_started) begin(); _mode = IDLE; write(true); }
void AlashBlinker::off() { if (!_started) begin(); _mode = IDLE; write(false); }
void AlashBlinker::toggle() { if (!_started) begin(); _mode = IDLE; write(!_state); }

void AlashBlinker::blink(uint16_t onMs, uint16_t offMs) {
  if (!_started) begin();
  _mode = BLINK;
  _on = onMs;
  _off = offMs;
  _since = millis();
  write(true);
}

void AlashBlinker::flash(uint8_t times, uint16_t onMs, uint16_t offMs) {
  if (!_started) begin();
  if (times == 0) { off(); return; }
  _mode = FLASH;
  _on = onMs;
  _off = offMs;
  _left = times;
  _since = millis();
  write(true);
}

void AlashBlinker::pattern(const uint16_t *durationsMs, uint8_t count, bool repeat) {
  if (!_started) begin();
  if (!durationsMs || count == 0) { off(); return; }
  _mode = PATTERN;
  _pat = durationsMs;
  _n = count;
  _idx = 0;
  _repeat = repeat;
  _since = millis();
  write(true);                             // первый отрезок шаблона это «включено»
}

void AlashBlinker::update() {
  if (_mode == IDLE) return;
  uint32_t now = millis();
  uint32_t el = now - _since;
  switch (_mode) {
    case BLINK:
      if (_state && el >= _on) { write(false); _since += _on; }
      else if (!_state && el >= _off) { write(true); _since += _off; }
      break;
    case FLASH:
      if (_state && el >= _on) {
        write(false);
        _since += _on;
        if (--_left == 0) _mode = IDLE;    // последняя вспышка закончилась
      } else if (!_state && el >= _off) {
        write(true);
        _since += _off;
      }
      break;
    case PATTERN:
      if (el >= _pat[_idx]) {
        _since += _pat[_idx];
        _idx++;
        if (_idx >= _n) {
          if (_repeat) _idx = 0;
          else { _mode = IDLE; write(false); break; }
        }
        write((_idx % 2) == 0);            // чётные отрезки включено, нечётные выключено
      }
      break;
    default: break;
  }
}
