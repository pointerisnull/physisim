#include "engine.h"
#include "object.h"

#include <stdint.h>
#include <sys/time.h>
#include <stdint.h>
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

double Engine::timedelta() {
  return dtime;
}

uint64_t Engine::get_tick() {
  return ticks;
}

void Engine::set_tick(uint64_t t) {
  ticks = t;
}

void Engine::tick() {
  dtime--;
  ticks++;
  sdelta = ((double)(current-last))/1000;
}

bool Engine::should_tick() {
  if (dtime >= 1) 
    return true;
  return false;
}

uint64_t unixtime() {
  struct timeval time;
  gettimeofday(&time, NULL);
  int64_t s1 = (int64_t)(time.tv_sec) * 1000;
  int64_t s2 = (time.tv_usec / 1000);
  return s1 + s2;
}

void Engine::update_time() {
  last = current;
  current = unixtime();
  dtime += (current - last)/interval;
}

Engine::Engine(int rate) {
  tps = rate;
  interval = 1000/tps;
  dtime = 0;
  sdelta = 0;
  last = unixtime();
  current = last;
}
