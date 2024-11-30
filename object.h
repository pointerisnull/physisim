#ifndef OBJ_H
#define OBJ_H

#include "pmath.h"

class Particle {
  private:
    float x, y, z;
    float m;
    Vec v, a;
    Vec forces[64];
    int fc;
    bool fixed;
  
  public:
    Particle(float x, float y, float z);
    void n2l();
    void applyforce(Vec f);
    void update();
};

class Segment {
  private:
    Particle *p1;
    Particle *p2;
    float length;
    bool fixed;
  public:
    Segment(Particle *pi, Particle *pf);
};

#define CIRCLE  = 0
#define BOX     = 1

class Object {
  private:
    Vec pos;
    Vec velocity;
    float angle;
    float vrot;

  public:
    float mass;
    float density;
    float elasticity;
    bool is_static;

    float width;
    float height;
    float area;
    float radius;
    
    int type;
    
    Object();
    
};

#endif
