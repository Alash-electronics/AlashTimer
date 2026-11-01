// AlashTimer: «один раз через 5 секунд». Светодиод включается сразу и сам выключается через 5 секунд (как лампа в подъезде).
// Повторный запуск: restart() (здесь по нажатию кнопки на пине 2, второй контакт на GND).
#include <AlashTimer.h>

AlashTimer lampOff(5000, AlashTimer::ONCE, false);   // false: пока не запущен
#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(2) == LOW) {            // нажали: включить и запустить отсчёт заново
    digitalWrite(LED_BUILTIN, HIGH);
    lampOff.restart();
  }
  if (lampOff.ready()) digitalWrite(LED_BUILTIN, LOW);   // сработал один раз
}
