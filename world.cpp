#include "world.h"

void World::step(float dtime) {
  for (int i = 0; i < objc; i++) {
    for (int j = 0; j < objc; j++) {
      
    }
    getobj(i)->step(dtime);
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
