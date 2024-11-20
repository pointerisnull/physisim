#include "object.h"

Particle::Particle(float x, float y, float z) {
  x = x;
  y = y;
  z = z;

}

void Particle::applyforce(Vec f) {
  forces[fc] = f;
}
//Fnet = ma
void n2l() {

}

void Particle::update() {
  a = {0, 0, 0};
}
