#include "world.h"

void World::addobj(Object obj) {
  objects.push_back(obj);
}

Object *World::getobj(int id) {
  return &objects.at(id);
}

Object World::copyobj(int id) {
  return objects.at(id);
}

World::World(int t) {
  type = t;
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

World::World() {}
