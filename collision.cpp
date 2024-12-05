#include "collision.h"
#include <stdio.h>

bool Collision::circle_int(Object a, Object b) {
  Vec ca = a.getpos(), cb = b.getpos();
  float ra = a.getradius(), rb = b.getradius();
  normal = ZERO;
  depth = 0.0f;

  float dist = distance(ca, cb);
  float radii = ra + rb;
  
  if (dist >= radii) return false;

  normal = normalize( sub(cb, ca) );
  depth = radii - dist;
  
  return true;
}

void Collision::resolve(Object *a, Object *b) {
  Vec vrelative = sub(b->velocity, a->velocity);
  
  if (dot(vrelative, normal) > 0.0f) return;

  float e = min(a->elasticity, b->elasticity);

  float j = -(1.0f + e) * dot(vrelative, normal);
  j /= 1/a->mass + 1/b->mass;

  Vec impulse = scale(normal, j);

  a->velocity = sub(a->velocity, scale(impulse, 1/a->mass));
  b->velocity = sum(b->velocity, scale(impulse, 1/b->mass));

}

void Collision::handle(Object *a, Object *b) {
  
  if (a->type == CIRCLE && b->type == CIRCLE && circle_int(*a, *b)) {
    a->move( scale(scale(scale(normal, -1.0f), depth), 0.5f) );
    b->move( scale(scale(normal, depth), 0.5f) );
    resolve(a, b);
  } else return;
}

Collision::Collision() {
  normal = ZERO;
  depth = 0.0f;
}
