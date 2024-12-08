#include "world.h"
#include "collision.h"
#include <stdio.h>

void World::step(float dtime) {
  for (int i = 0; i < objc; i++) {
    getobj(i)->step(dtime);
  }
}

void World::handle_collisions() {
  Collision coll;
  for (int i = 0; i < objc-1; i++) {
    for (int j = i+1; j < objc; j++) {
      coll.handle(getobj(i), getobj(j));
    }
  }
}

void World::addobj(Object obj) {
  objects.push_back(obj);
  objc++;
}

Object *World::getobj(int id) {
  return &objects.at(id);
}

Object World::copyobj(int id) {
  return objects.at(id);
}

World::World(int t) {
  type = t;
  objc = 0;
  switch (type) {
    case SPACE:
      gravity = 0;
      drag = false;
      break;
    case FLAT:
      gravity = g;
      drag = true;
      break;
    case PLANET: //todo
      gravity = g;
      drag = true;
      break;
    default:
      break;
  }
}

World::World() {
  objc = 0;
}
