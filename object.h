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

#endif
