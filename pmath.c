#include <math.h>
#include "pmath.h"

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
