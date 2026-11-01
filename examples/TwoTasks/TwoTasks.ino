// AlashTimer: две задачи с разным периодом в одном loop(): датчик читается каждые 2 секунды, светодиод мигает каждые 300 мс.
// С delay() так не сделать: он останавливает всё.
#include <AlashTimer.h>

AlashTimer readSensor(2000);
AlashTimer blinkTimer(300);
#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (blinkTimer.ready()) digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  if (readSensor.ready()) {
    Serial.print("Чтение датчика, A0 = ");
    Serial.println(analogRead(A0));
  }
}
