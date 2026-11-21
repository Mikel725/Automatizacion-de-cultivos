#include "Arduino.h"
#include "Timer.h"

Timer::Timer() {
  TCCR1A = 0;
  TCCR1B = 0;
}

void Timer::init(uint16_t preescalado, uint16_t numero_ticks) {

  this->preescalado = preescalado;
  this->numero_ticks = numero_ticks;

  TCCR1A = 0;
  TCCR1B = 0;

  //Limpiar registro contador
  TCNT1 = 0;

  //Modo CTC
  TCCR1B |= (1 << WGM12);

  //Activamos interrupción
  TIMSK1 |= (1 << OCIE1A);

}

void Timer::start() {

  //Numero de ciclos a alcanzar
  OCR1A = numero_ticks;

  TCCR1B &= 0b11111000;

  uint8_t bits_cs = 0;

  switch (preescalado) {
    case 1:
      bits_cs = (1 << CS10);
      break;
    case 8:
      bits_cs = (1 << CS11);
      break;
    case 64:
      bits_cs = (1 << CS11) | (1 << CS10);
      break;
    case 256:
      bits_cs = (1 << CS12);
      break;
    case 1024:
      bits_cs = (1 << CS12) | (1 << CS10);
      break;

    default: return;
  }

  TCCR1B |= bits_cs;
}

void Timer::pause() {

  uint8_t mascara = 0b11111000;

  //Desactivamos CS10 -CS12
  TCCR1B &= mascara;

  //Ponemos el registro contador a 0
  TCNT1 = 0;
}
