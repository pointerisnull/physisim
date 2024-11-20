#include <iostream>
#include <stdint.h>
#include <sys/time.h>
#include <stdint.h>

#include "engine.h"
#include <vector>

int64_t currentTime() {
  struct timeval time;
  gettimeofday(&time, NULL);
  int64_t s1 = (int64_t)(time.tv_sec) * 1000;
  int64_t s2 = (time.tv_usec / 1000);
  return s1 + s2;
}

int main(int argc, char **argv) {
  int ticksPerSecond = 60;
  double interval = 1000/ticksPerSecond;
  double deltaTime = 0;
  int64_t last = currentTime();
  int64_t current;
  
  Engine engine;
  engine.init((char *)"Physisim", 720, 480);
  engine.set_tick(0);

	while (engine.is_running) { 
    current = currentTime();
    deltaTime += (current - last)/interval;
    last = current;
    //scanInput(&world, &p);
    engine.check_events();
    if (deltaTime >= 1) {
      deltaTime--;
      engine.tick();
      //std::cout << engine.get_tick() << std::endl;
	  }
    engine.update();
    
    if (engine.get_tick() > 1000)
      engine.is_running = 0;
	}

	return 0;
}
