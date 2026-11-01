# AlashTimer

[Русский](#русский) | [Қазақша](#қазақша) | [English](#english)

---

## Русский

Простая библиотека, которая заменяет `delay()` и ручные `millis()`: **«раз в секунду»**, **«через 5 секунд один раз»**, секундомер и **мигающий светодиод** по шаблону. Пока таймер ждёт, программа делает другое. Без зависимостей.

```cpp
#include <AlashTimer.h>
AlashTimer everySecond(1000);

void setup() { Serial.begin(115200); }
void loop() {
  if (everySecond.ready()) Serial.println("tick");   // раз в секунду, loop() не стоит
}
```

### Что умеет
- **`ready()` одной строкой:** true один раз за период; фаза сохраняется, ошибка не копится.
- **Один раз:** `AlashTimer t(5000, AlashTimer::ONCE)`; перезапуск `restart()`.
- **Пауза и секундомер:** `pause()`, `resume()`, `elapsed()`, `remaining()`, `progress()`.
- **Безопасно через 49 суток:** переполнение `millis()` учтено.
- **Если программа была занята:** пропущенные срабатывания не вываливаются пачкой, `missed()` скажет, сколько их было.
- **Микросекунды:** `setMicros(true)`.
- **Обработчик:** `onTick(fn)` и `update()`.
- **`AlashBlinker`:** `blink(вкл, выкл)`, `flash(3)`, `pattern(массив, число)` (например, SOS), светодиод с активным LOW.
- Работает на **Arduino AVR, ESP32, ESP8266**.

### Чем отличается от других библиотек
Мы посмотрели Ticker, SimpleTimer, arduino-timer (contrem) и millisDelay:
- Ticker только для ESP и работает через прерывания; у нас простой опрос, одинаково на всех платах.
- SimpleTimer/arduino-timer накапливают задержку или требуют `tick()` и хранения обработчиков; у нас `if (t.ready())`.
- Ни в одной нет мигалки по шаблону и секундомера в одном классе.

### Примеры
`Basic`, `TwoTasks`, `Once`, `Blinker`, `Stopwatch`

### Тесты
Период без накопления ошибки, один раз, пропущенные срабатывания, переполнение `millis()`, пауза, микросекунды, мигание, вспышки и SOS проверены без железа: `extras/test`.

Подробное руководство: [docs/WIKI.md](docs/WIKI.md).

---

## Қазақша

`delay()` пен қолмен `millis()` орнына жүретін қарапайым кітапхана: **«секунд сайын»**, **«5 секундтан кейін бір рет»**, секундомер және шаблон бойынша **жыпылықтайтын жарықдиод**. Таймер күтіп тұрғанда бағдарлама басқа іс істейді. Тәуелділіксіз.

```cpp
#include <AlashTimer.h>
AlashTimer everySecond(1000);

void setup() { Serial.begin(115200); }
void loop() {
  if (everySecond.ready()) Serial.println("tick");   // раз в секунду, loop() не стоит
}
```

### Мүмкіндіктері
- **`ready()` бір жолмен:** кезең сайын бір рет true; қателік жиналмайды.
- **Бір рет:** `AlashTimer t(5000, AlashTimer::ONCE)`; `restart()`.
- **Үзіліс және секундомер:** `pause()`, `resume()`, `elapsed()`, `remaining()`, `progress()`.
- **49 тәуліктен кейін де қауіпсіз:** `millis()` толуы ескерілген.
- **Бағдарлама бос болмаса:** өткізілген іске қосулар шоғырланбайды, `missed()` санын айтады.
- **Микросекунд:** `setMicros(true)`.
- **Өңдеуші:** `onTick(fn)` және `update()`.
- **`AlashBlinker`:** `blink(қос, өшір)`, `flash(3)`, `pattern(массив, саны)` (мысалы, SOS).
- **Arduino AVR, ESP32, ESP8266** тақталарында жұмыс істейді.

### Басқа кітапханалардан айырмашылығы
Ticker, SimpleTimer, arduino-timer және millisDelay қарадық:
- Ticker тек ESP үшін; бізде қарапайым сұрау, барлық тақтада бірдей.
- Бізде `if (t.ready())` жеткілікті.
- Ешқайсысында үлгі бойынша жыпылықтау мен секундомер бір класта жоқ.

### Мысалдар
`Basic`, `TwoTasks`, `Once`, `Blinker`, `Stopwatch`

### Тесттер
Кезең, бір рет, өткізілген іске қосулар, `millis()` толуы, үзіліс, жыпылықтау және SOS тексерілген: `extras/test`.

Толық нұсқаулық: [docs/WIKI.md](docs/WIKI.md).

---

## English

A simple library that replaces `delay()` and hand-written `millis()`: **"every second"**, **"once after 5 seconds"**, a stopwatch and a **blinking LED** by pattern. While the timer waits, the program does other things. No dependencies.

```cpp
#include <AlashTimer.h>
AlashTimer everySecond(1000);

void setup() { Serial.begin(115200); }
void loop() {
  if (everySecond.ready()) Serial.println("tick");   // раз в секунду, loop() не стоит
}
```

### Features
- **`ready()` in one line:** true once per period; the phase is kept, error does not accumulate.
- **Once:** `AlashTimer t(5000, AlashTimer::ONCE)`; restart with `restart()`.
- **Pause and stopwatch:** `pause()`, `resume()`, `elapsed()`, `remaining()`, `progress()`.
- **Safe after 49 days:** `millis()` overflow is handled.
- **If the program was busy:** missed ticks do not burst out; `missed()` tells how many there were.
- **Microseconds:** `setMicros(true)`.
- **Callback:** `onTick(fn)` and `update()`.
- **`AlashBlinker`:** `blink(on, off)`, `flash(3)`, `pattern(array, count)` (for example SOS), active-LOW LEDs.
- Works on **Arduino AVR, ESP32, ESP8266**.

### How it differs from other libraries
We looked at Ticker, SimpleTimer, arduino-timer and millisDelay:
- Ticker is ESP-only and interrupt-based; ours is simple polling, identical on every board.
- SimpleTimer/arduino-timer accumulate delay or need handler tables; ours is `if (t.ready())`.
- None has a pattern blinker and a stopwatch in one class.

### Examples
`Basic`, `TwoTasks`, `Once`, `Blinker`, `Stopwatch`

### Tests
Period without drift, once, missed ticks, `millis()` overflow, pause, microseconds, blink, flash and SOS are checked without hardware: `extras/test`.

Full guide: [docs/WIKI.md](docs/WIKI.md).

---

MIT License, Alash Electronics.
