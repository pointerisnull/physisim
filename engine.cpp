#include "engine.h"
#include <stdio.h>

void Engine::init(char *title, int w, int h) {
    is_running = 1;
    set_tick(0);
    win.create(title, w, h); 
}

uint64_t Engine::get_tick() {
    return ticks;
}

void Engine::set_tick(uint64_t setter) {
  ticks = setter;
}

void Engine::update() {
  if (win.running)
    win.draw();
  if (ticks != tick_last) {
    //do physics
    tick_last = ticks;
  }
}

void Engine::tick() {
  ticks++;
}

void Engine::check_events() {
  if (!win.running) {
    is_running = 0;
    win.kill();
  } else {
    win.check_updates();
  }
}
