#include "engine.h"
#include "object.h"
#include <stdio.h>
#include <math.h>

void Engine::update() {
  Object p({50*cos((float)ticks*0.02)+256, 256.0 - 50*sin((float)ticks*0.02), 0}, 1, 1, false);
  Object c({0.08 + (float)ticks*0.2, 50-sin((float)ticks*0.01)*20, 0}, 20, 1, 1, false);

  if (window.running) {
    window.clear();
    window.draw(p);
    window.draw(c);
    window.update();
  }
  if (ticks != tick_last) {
    //do physics
    tick_last = ticks;
  }
}

void Engine::check_events() {
  if (!window.running) {
    is_running = 0;
    window.kill();
  } else {
    window.check_updates();
  }
}

void Engine::init(char *title, int w, int h) {
  is_running = 1;
  set_tick(0);
  Window win(title, w, h);
  World wld(FLAT);

  window = win;
  world = wld;
}

void Engine::timedelta(uint64_t current, uint64_t last) {
  dtime = ((double)(current-last))/1000;
  
  printf("Time delta: %lf seconds\n", dtime);
}

uint64_t Engine::get_tick() {
    return ticks;
}

void Engine::set_tick(uint64_t t) {
  ticks = t;
}

void Engine::tick() {
  ticks++;
}
