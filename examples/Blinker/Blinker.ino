// [ru] AlashBlinker: мигание по шаблону без delay(). Бесконечное мигание, три вспышки и сигнал SOS.
//      update() нужно вызывать в loop().
// [kk] AlashBlinker: delay() жоқ үлгі бойынша жыпылықтау. Шексіз жыпылықтау, үш жарқыл және SOS сигналы.
//      update() функциясын loop() ішінде шақыру керек.
// [en] AlashBlinker: blinking by a pattern without delay(). Endless blinking, three flashes and the SOS signal.
//      update() must be called in loop().
#include <AlashTimer.h>

#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif
AlashBlinker led(LED_BUILTIN);
AlashTimer change(6000);
uint8_t step = 0;
const uint16_t sos[] = {150, 150, 150, 150, 150, 450, 450, 150, 450, 150, 450, 450, 150, 150, 150, 150, 150, 900};

void setup() {
  led.blink(100, 900);                    // 0.1 с включено, 0.9 с выключено
}

void loop() {
  led.update();
  if (change.ready()) {                   // каждые 6 секунд новый режим
    step = (step + 1) % 3;
    if (step == 0) led.blink(100, 900);
    if (step == 1) led.flash(3, 100, 100);          // три вспышки и тишина
    if (step == 2) led.pattern(sos, 18, true);      // SOS по кругу
  }
}
