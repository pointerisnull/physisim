
#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H

#include <stdint.h>
#include "display.h"

class Engine {
  private:
    uint64_t ticks;
    uint64_t tick_last;
    Window win;

  public:
    uint8_t is_running;

    void init(char *title, int w, int h);
    void tick();
    uint64_t get_tick();
    void set_tick(uint64_t setter);
    void update();
    void check_events();
    
    void debug_print();
};

#endif
