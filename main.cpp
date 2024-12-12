/*******************************\
*           PHYSîSîM            *
* ============================= *
* Physics simulator & scripting *
*           language.           *
*                               *
*   -Brendan Haney, 2024        *
\*******************************/
#define VERSION 0.1.0

#include "engine.h"

int main(int argc, char **argv) {
  
  Engine engine(60);
  engine.init((char *)"Physîsîm", 720, 480, argv[1]);
  engine.set_tick(0);
  
 
	while (engine.is_running) { 
    engine.update_time();
    engine.check_events();
    
    if (engine.should_tick())
      engine.tick();
    
    engine.update();
	}
  
	return 0;
}
