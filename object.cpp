#include "object.h"
#include <math.h>
#include <stdio.h>

Object::Object() {};

Object::Object(Vec pos, float density, float mass, float restitution, float area, bool is_static, float radius, float width, float height, int type) {
  pos = pos;
  velocity = {0, 0, 0};
  angle = 0;
  vrot = 0;

  mass = mass;
  density = density;
  elasticity = restitution;
  is_static = is_static;

  width = width;
  height = height;
  radius = radius;
  area = area;
    
  type = type;

}
//particle
Object::Object(Vec p, float m, float d, float is_s) {
  pos = p;
  velocity = {0, 0, 0};
  angle = 0;
  vrot = 0;

  mass = m;
  density = d;
  elasticity = 0;
  is_static = is_s;

  width = 0;
  height = 0;
  radius = 0;
  area = 0;
    
  type = PARTICLE;
}
//circle
Object::Object(Vec p, float r, float m, float d, float is_s) {
  pos = p;
  velocity = {0, 0, 0};
  angle = 0;
  vrot = 0;

  mass = m;
  density = d;
  elasticity = 0;
  is_static = is_s;

  width = 0;
  height = 0;
  radius = r;
  area = M_PI*radius*radius;
    
  type = CIRCLE;
}
//rectangle
Object::Object(Vec p, float w, float h, float m, float d, float is_s) {
  pos = p;
  velocity = {0, 0, 0};
  angle = 0;
  vrot = 0;

  mass = m;
  density = d;
  elasticity = 0;
  is_static = is_s;

  width = w;
  height = h;
  radius = 0;
  area = width*height;
    
  type = BOX;
}
