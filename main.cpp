#include "engine.h"
#include "pscript.h"

int main(int argc, char **argv) {
  
  Engine engine(60);
  engine.init((char *)"Physisim", 720, 480);
  engine.set_tick(0);
  /*
  Interpreter interp;
  interp.read_file((char *)"hello.chop");
  interp.run_code();
  */
	while (engine.is_running) { 
    engine.update_time();
    engine.check_events();
    
    if (engine.should_tick())
      engine.tick();
    
    engine.update();
    /*
    if (engine.get_tick() > 1000)
      engine.is_running = 0;*/
	}

	return 0;
}
