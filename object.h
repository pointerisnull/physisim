#ifndef OBJ_H
#define OBJ_H

#include "pmath.h"
#include <vector>

#define PARTICLE  0
#define CIRCLE    1
#define BOX       2

class Object {
  private:
    float angle;
    float vrot;

  public:
    Vec fnet;
    Vec pos;
    Vec velocity;
    float mass;
    float density;
    float elasticity;
    bool equalibrium;
    bool is_static;

    float width;
    float height;
    float area;
    float radius;
    
    int type;

    void applyforce(Vec force);
    void step(float dtime);
    void move(Vec v);
    void moveto(Vec p);

    Vec getpos();
    float getmass();
    void setmass(float m);
    float getradius();
    void setradius(float r);
    void setwidth(float w);
    void setheight(float h);
    void setvel(Vec v);
    void setpos(Vec p);
    void setdens(float d);
    void setelas(float e);
    
    Object();
    Object(Vec pos, float density, float mass, float restitution, float area, bool is_static, float radius, float width, float height, int type); //GENERIC
    Object(Vec pos, float mass, float density, float is_static); //PARTICLE
    Object(Vec pos, float radius, float mass, float density, float elasticity, float is_static); //CIRCLE
    Object(Vec pos, float width, float height, float mass, float density, float elasticity, float is_static); //BOX
    
};
/*
class Particle {
  private:
    Vec velocity;

  public:
    vec pos;
    float mass;
}*/

#endif
