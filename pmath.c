#include <math.h>
#include <float.h>
#include "pmath.h"

#define EPSILON FLT_EPSILON 

float magnitude(Vec a) {
  return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

float distance(Vec a, Vec b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;
  float dz = a.z - b.z;
  return sqrt(dx*dx + dy*dy + dz*dz);
}

float angle(Vec a, Vec b) {
  float m = magnitude(a) * magnitude(b);
  float d = dot(a, b);
  return acos(d/m);
}

float dot(Vec a, Vec b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

float min(float a, float b) {
  return (a <= b) ? a : b;
}

int fcomp(float a, float b) {
  if (fabs(a-b) < EPSILON)
    return 1;
  return 0;
}

int vcomp(Vec a, Vec b) {
  if ( 
     (fabs(a.x - b.x) < EPSILON) &&
     (fabs(a.y - b.y) < EPSILON) &&
     (fabs(a.z - b.z) < EPSILON)
     )
    return 1;
  return 0;
}

Vec sum(Vec a, Vec b) {
  return {
    (a.x + b.x), 
    (a.y + b.y), 
    (a.z + b.z) 
  }; 
}

Vec sub(Vec a, Vec b) {
  return {
    (a.x - b.x), 
    (a.y - b.y), 
    (a.z - b.z) 
  }; 
}

Vec scale(Vec a, float s) {
  return {
    (a.x*s), 
    (a.y*s), 
    (a.z*s) 
  }; 
}

Vec cross(Vec a, Vec b) {
  return {
    (a.y*b.z - a.z*b.y), 
    (a.z*b.x - a.x*b.z), 
    (a.x*b.y - a.y*b.x)
  };
}

Vec normalize(Vec a) {
  float len = magnitude(a);
  return {a.x / len, a.y/len, a.z/len};
}
