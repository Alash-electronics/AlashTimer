// [ru] AlashTimer: «один раз через 5 секунд». Светодиод включается сразу и сам выключается через 5 секунд (как лампа в подъезде).
//      Повторный запуск: restart() (здесь по нажатию кнопки на пине 2, второй контакт на GND).
// [kk] AlashTimer: «5 секундтан кейін бір рет». Жарықдиод бірден қосылады және 5 секундтан кейін өзі өшеді (кіреберістегі шам сияқты).
//      Қайта іске қосу: restart() (мұнда 2 пиндегі батырманы басу арқылы, екінші түйіспе GND-ға).
// [en] AlashTimer: "once after 5 seconds". The LED switches on at once and switches itself off after 5 seconds (like a lamp in a stairwell).
//      To start again: restart() (here by a button press on pin 2, the other contact to GND).
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
