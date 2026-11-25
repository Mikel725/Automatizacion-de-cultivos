#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"
#include "stdint.h"

class Timer {

  public:

    Timer();

    void init(uint16_t preescalado, uint16_t numero_ticks);
    void start();
    void pause();

  private:
    uint16_t preescalado;
    uint16_t numero_ticks;
};

#endif