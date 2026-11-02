// [ru] AlashTimer как секундомер: elapsed() показывает, сколько прошло. Кнопка на пине 2 (второй контакт на GND):
//      первое нажатие запускает, второе останавливает и печатает время.
// [kk] AlashTimer секундомер ретінде: elapsed() қанша уақыт өткенін көрсетеді. 2 пиндегі батырма (екінші түйіспе GND-ға):
//      бірінші басу іске қосады, екіншісі тоқтатады және уақытты басып шығарады.
// [en] AlashTimer as a stopwatch: elapsed() shows how much has passed. The button on pin 2 (the other contact to GND):
//      the first press starts, the second stops and prints the time.
#include <AlashTimer.h>

AlashTimer watch(4000000000UL, AlashTimer::ONCE, false);   // очень длинный интервал: нужен только отсчёт
bool wasDown = false;

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  Serial.println("Нажмите кнопку: старт, ещё раз: стоп.");
}

void loop() {
  bool down = digitalRead(2) == LOW;
  if (down && !wasDown) {
    delay(30);                            // грубая защита от дребезга; для кнопок лучше библиотека AlashButton
    if (watch.isRunning()) {
      Serial.print("Время: ");
      Serial.print(watch.elapsed() / 1000.0, 2);
      Serial.println(" с");
      watch.stop();
    } else {
      watch.start();
      Serial.println("Пошло...");
    }
  }
  wasDown = down;
}
