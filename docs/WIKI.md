# AlashTimer: руководство / нұсқаулық / guide

[Русский](#русский) | [Қазақша](#қазақша) | [English](#english)

---

## Русский

Простая библиотека, которая заменяет `delay()` и ручные `millis()`: **«раз в секунду»**, **«через 5 секунд один раз»**, секундомер и **мигающий светодиод** по шаблону. Пока таймер ждёт, программа делает другое. Без зависимостей.

### Установка
Arduino IDE: Скетч, Подключить библиотеку, Управлять библиотеками, найти **AlashTimer** и нажать Установить. Или скачайте ZIP с GitHub: Скетч, Подключить библиотеку, Добавить .ZIP библиотеку.

### Платы
Arduino Uno / Nano / Mega (AVR), ESP32, ESP8266 и другие, где работает Arduino-ядро.

### Быстрый старт
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

### Справочник по методам
| Метод | Что делает |
|---|---|
| `AlashTimer(ms, mode, autoStart)` | Создать таймер: период в мс, PERIODIC или ONCE |
| `ready()` | Пора? true один раз за период |
| `start() / stop() / restart()` | Запустить с нуля / остановить |
| `pause() / resume()` | Пауза без потери прошедшего времени |
| `elapsed() / remaining() / progress()` | Прошло / осталось / доля 0..1 |
| `count() / missed()` | Сколько раз сработал / пропущено |
| `onTick(fn) + update()` | Вызвать функцию, когда пора |
| `AlashBlinker(pin, activeLow)` | Светодиод или любой выход |
| `blink(on, off) / flash(n) / pattern(arr, n)` | Мигать / N вспышек / свой шаблон |
| `on() / off() / toggle() / update()` | Включить, выключить, переключить; update() в loop() |

### Если что-то не работает
**ready() срабатывает не точно в срок**

Сработает, как только loop() до него дойдёт. Не используйте `delay()` в loop() и не делайте долгих операций: тогда точность будет в пределах миллисекунд.

**Таймер не срабатывает**

Проверьте, что он запущен: `isRunning()`. Таймеры ONCE после срабатывания останавливаются, для повтора вызовите `restart()`. Если создали с `autoStart = false`, вызовите `start()`.

**Светодиод не мигает**

Вызывайте `led.update()` в каждом проходе loop(). Для светодиода, включаемого уровнем LOW, создайте `AlashBlinker led(пин, true)`.

### Самопроверка
В библиотеке есть `diagnose(Serial)`: она печатает, что видит плата, и подсказывает, что проверить. Язык подсказок: `setLanguage(LANG_RU / LANG_KK / LANG_EN)`.

### Примеры
`Basic`, `TwoTasks`, `Once`, `Blinker`, `Stopwatch`

---

## Қазақша

`delay()` пен қолмен `millis()` орнына жүретін қарапайым кітапхана: **«секунд сайын»**, **«5 секундтан кейін бір рет»**, секундомер және шаблон бойынша **жыпылықтайтын жарықдиод**. Таймер күтіп тұрғанда бағдарлама басқа іс істейді. Тәуелділіксіз.

### Орнату
Arduino IDE: Sketch, Include Library, Manage Libraries, **AlashTimer** табып, Install басыңыз. Немесе GitHub-тан ZIP жүктеп, Sketch, Include Library, Add .ZIP Library.

### Тақталар
Arduino Uno / Nano / Mega (AVR), ESP32, ESP8266 және Arduino ядросы бар басқалар.

### Жылдам бастау
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

### Әдістер анықтамасы
| Әдіс | Не істейді |
|---|---|
| `AlashTimer(ms, mode, autoStart)` | Таймер жасау |
| `ready()` | Уақыт болды ма? |
| `start() / stop() / restart()` | Іске қосу / тоқтату |
| `pause() / resume()` | Үзіліс |
| `elapsed() / remaining() / progress()` | Өтті / қалды / үлесі |
| `count() / missed()` | Қанша рет / өткізілген |
| `onTick(fn) + update()` | Уақыт болғанда функцияны шақыру |
| `AlashBlinker(pin, activeLow)` | Жарықдиод немесе кез келген шығыс |
| `blink(on, off) / flash(n) / pattern(arr, n)` | Жыпылықтау / N жарқыл / өз үлгісі |
| `on() / off() / toggle() / update()` | Қосу, өшіру, ауыстыру |

### Бірдеңе жұмыс істемесе
**ready() дәл уақытында істемейді**

loop() оған жеткенде істейді. loop() ішінде `delay()` қолданбаңыз.

**Таймер істемейді**

`isRunning()` тексеріңіз. ONCE таймері істегеннен кейін тоқтайды, қайталау үшін `restart()`.

**Жарықдиод жыпылықтамайды**

Әр loop() сайын `led.update()` шақырыңыз. LOW қосатын болса, `AlashBlinker led(пин, true)`.

### Өзін-өзі тексеру
Кітапханада `diagnose(Serial)` бар: тақта не көргенін басып шығарады және нені тексеру керегін айтады. Кеңес тілі: `setLanguage(LANG_RU / LANG_KK / LANG_EN)`.

### Мысалдар
`Basic`, `TwoTasks`, `Once`, `Blinker`, `Stopwatch`

---

## English

A simple library that replaces `delay()` and hand-written `millis()`: **"every second"**, **"once after 5 seconds"**, a stopwatch and a **blinking LED** by pattern. While the timer waits, the program does other things. No dependencies.

### Installation
Arduino IDE: Sketch, Include Library, Manage Libraries, search **AlashTimer** and click Install. Or download the ZIP from GitHub: Sketch, Include Library, Add .ZIP Library.

### Boards
Arduino Uno / Nano / Mega (AVR), ESP32, ESP8266 and others with an Arduino core.

### Quick start
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

### Method reference
| Method | What it does |
|---|---|
| `AlashTimer(ms, mode, autoStart)` | Create a timer: period in ms, PERIODIC or ONCE |
| `ready()` | Is it time? true once per period |
| `start() / stop() / restart()` | Start from zero / stop |
| `pause() / resume()` | Pause keeping elapsed time |
| `elapsed() / remaining() / progress()` | Elapsed / remaining / fraction 0..1 |
| `count() / missed()` | Fires so far / missed ticks |
| `onTick(fn) + update()` | Call a function when due |
| `AlashBlinker(pin, activeLow)` | LED or any output |
| `blink(on, off) / flash(n) / pattern(arr, n)` | Blink / N flashes / custom pattern |
| `on() / off() / toggle() / update()` | On, off, toggle; update() in loop() |

### If something does not work
**ready() does not fire exactly on time**

It fires as soon as loop() reaches it. Do not use `delay()` in loop() or long operations; then accuracy is within milliseconds.

**The timer never fires**

Check `isRunning()`. ONCE timers stop after firing, call `restart()` to repeat. If created with `autoStart = false`, call `start()`.

**The LED does not blink**

Call `led.update()` on every pass of loop(). For active-LOW LEDs create `AlashBlinker led(pin, true)`.

### Self-check
The library has `diagnose(Serial)`: it prints what the board sees and tells what to check. Tips language: `setLanguage(LANG_RU / LANG_KK / LANG_EN)`.

### Examples
`Basic`, `TwoTasks`, `Once`, `Blinker`, `Stopwatch`

---

MIT License, Alash Electronics. https://github.com/Alash-electronics/AlashTimer
