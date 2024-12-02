
#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H

#include <stdint.h>
#include "display.h"
#include "world.h"

class Engine {
  private:
    uint64_t ticks;
    uint64_t tick_last;
    double dtime; //seconds
    Window window;
    World world;

  public:
    uint8_t is_running;

    void init(char *title, int w, int h);
    void tick();
    void timedelta(uint64_t current, uint64_t last);
    void set_tick(uint64_t t);
    uint64_t get_tick();
    void update();
    void check_events();
    
    void debug_print();
};

#endif
