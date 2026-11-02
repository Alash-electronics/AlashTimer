// [ru] AlashTimer: «раз в секунду» без delay(). Программа не стоит на месте: пока таймер ждёт, loop() крутится.
// [kk] AlashTimer: delay() жоқ «секунд сайын». Бағдарлама тұрып қалмайды: таймер күтіп тұрғанда loop() айнала береді.
// [en] AlashTimer: "once a second" without delay(). The program does not stand still: while the timer waits, loop() keeps running.
#include <AlashTimer.h>

AlashTimer everySecond(1000);             // период 1000 мс

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (everySecond.ready()) {              // true один раз за период, без накопления ошибки
    Serial.print("Прошло секунд: ");
    Serial.println(everySecond.count());
  }
  // Здесь можно делать что угодно ещё: опрашивать кнопки, датчики...
}
