#ifndef ENGINE_CLASS_H
#define ENGINE_CLASS_H

#include <stdint.h>
#include "display.h"
#include "world.h"
#include "pscript.h"

class Engine {
  private:
    uint64_t ticks;
    uint64_t tick_last;
    int tps;        //ticks per second
    double interval;
    double dtime;   //milliseconds
    double sdelta;  //seconds
    int64_t last;
    int64_t current;
    int evc;

    Window window;
    World world;
    Interpreter interp;

  public:
    void init(char *title, int w, int h);
    void update_time();
    double timedelta();
    bool should_tick();
    void set_tick(uint64_t t);
    uint64_t get_tick();
    void tick();
    void update();
    void check_events();
    void shutdown();
    void debug_print();

    Engine(int tps);
    
    uint8_t is_running;
};

#endif
