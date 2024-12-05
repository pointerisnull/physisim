#ifndef WORLD_H
#define WORLD_H

#include "pmath.h"
#include "object.h"
#include <vector>
#define SPACE   0
#define FLAT    1 
#define PLANET  2

class World {
  private:
    float gravity;
    bool drag;
    std::vector<Object> objects;

  public:
    int type;
    int objc;
    
    void addobj(Object obj);
    Object *getobj(int id);
    Object copyobj(int id);
    void step(float dtime);
    void handle_collisions();

    World();
    World(int type); 
};

/*
  float minsize     = 0.001f;
  float maxsize     = 1028.0f;
  float mindensity  = 0.2f; 
  float maxdensity  = 32.0f; 
 */

#endif
