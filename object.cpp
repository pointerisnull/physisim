#include "object.h"
#include <math.h>
#include <stdio.h>

void Object::step(float dtime) {
  if (!equalibrium) {
    Vec acceleration = { // newton's second law
      fnet.x/mass, fnet.y/mass, fnet.z/mass
    };
    velocity = sum(velocity, acceleration); //velocity += acceleration;
    
    //printf("velocity = %f m/s\n\n", magnitude(velocity));
    
    fnet = ZERO;
    equalibrium = true;
  }
  pos = sum(pos, scale(velocity, dtime)); //pos += velocity * deltaTime;
}

void Object::applyforce(Vec force) {
  fnet.x += force.x; 
  fnet.y += force.y; 
  fnet.z += force.z; 
  
  equalibrium = false;
}

void Object::move(Vec v) {
  pos = sum(pos, v);
}

void Object::moveto(Vec p) {
  pos = p;
}

Vec Object::getpos() {
  return pos;
}

void Object::setmass(float m) {
  mass = m;
}

void Object::setradius(float r) {
  radius = r;
}

void Object::setwidth(float r) {
  width = r;
}

void Object::setheight(float r) {
  height = r;
}

void Object::setpos(Vec p) {
  pos = p;
}

void Object::setdens(float d) {
  density = d;
}

void Object::setelas(float e) {
  elasticity = e;
}

void Object::setvel(Vec v) {
  velocity = v;
}

float Object::getmass() {
  return mass;
}

float Object::getradius() {
  return radius;
}



Object::Object(Vec pos, float density, float mass, float restitution, float area, bool is_static, float radius, float width, float height, int type) {
  pos = pos;
  velocity = {0, 0, 0};
  fnet = {0, 0, 0};
  angle = 0;
  vrot = 0;

  mass = mass;
  density = density;
  elasticity = restitution;
  equalibrium = true;
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
  fnet = {0, 0, 0};
  angle = 0;
  vrot = 0;

  mass = m;
  density = d;
  elasticity = 0.2;
  equalibrium = true;
  is_static = is_s;

  width = 0;
  height = 0;
  radius = 0;
  area = 0;
    
  type = PARTICLE;
}
//circle
Object::Object(Vec p, float r, float m, float d, float e, float is_s) {
  pos = p;
  velocity = {0, 0, 0};
  fnet = {0, 0, 0};
  angle = 0;
  vrot = 0;

  mass = m;
  density = d;
  elasticity = e;
  equalibrium = true;
  is_static = is_s;

  width = 0;
  height = 0;
  radius = r;
  area = M_PI*radius*radius;
    
  type = CIRCLE;
}
//rectangle
Object::Object(Vec p, float w, float h, float m, float d, float e, float is_s) {
  pos = p;
  velocity = {0, 0, 0};
  fnet = {0, 0, 0};
  angle = 0;
  vrot = 0;

  mass = m;
  density = d;
  elasticity = e;
  is_static = is_s;

  width = w;
  height = h;
  radius = 0;
  area = width*height;
    
  type = BOX;
}

Object::Object() {
  pos = {0, 0, 0};
  velocity = {0, 0, 0};
  fnet = {0, 0, 0};
  angle = 0;
  vrot = 0;

  mass = 0.1;
  density = 0.1;
  elasticity = 0.1;
  equalibrium = true;
  is_static = false;

  width = 1;
  height = 1;
  radius = 1;
  area = 0;
    
  type = PARTICLE;


};
