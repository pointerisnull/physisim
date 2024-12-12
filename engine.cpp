#include "engine.h"
#include "object.h"
#include "world.h"

#include <stdint.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

void Engine::update() {
  if (window.running) {
    window.clear();
    window.draw(world);
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

void Engine::init(char *title, int w, int h, char *fp) {
  is_running = 1;
  set_tick(0);
  Window win(title, w, h);
  World wld(FLAT);

  window = win;
  world = wld;
  
  evc = 0;
  interp.read_file(fp);
  interp.run_code();

  for (int i = 0; i < interp.objc; i++) {
    world.addobj(interp.objs.at(i));
  }
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
  
  world.handle_collisions();
  world.step(sdelta);
  
  if ( evc < interp.eventc && interp.eventc > 0) {
    for (int i = 0; i < interp.eventc; i++) {
      event *ev = &interp.events.at(i);
      if ( !ev->done && (uint64_t)(ev->time * tps) <= ticks) {
        printf("applying force at %ld, %d\n", ticks, ev->time);
        printf("index: %d, %d\n", ev->oi, ev->fi);
        printf("f: %f \n", interp.vecs.at(ev->fi).x);
        world.getobj(ev->oi)->applyforce(interp.vecs.at(ev->fi));
        ev->done = true;
        evc++;
      }
    }
  }
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

void Engine::shutdown() {
  window.kill();
  is_running = 0;
}

Engine::Engine(int rate) {
  tps = rate;
  interval = 1000/tps;
  dtime = 0;
  sdelta = 0;
  last = unixtime();
  current = last;
  
}
