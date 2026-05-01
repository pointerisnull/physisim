#include "world.hpp"
#include "../physics/collision.hpp"

#include <cstdio>

void World::step(float dtime) {

	for (int i = 0; i < objc; i++) 
		get_obj(i)->step(dtime);

}

void World::handle_collisions() {

	Collision coll;

	// TODO: Write better algorithm!
	for (int i = 0; i < objc-1; i++) 
		for (int j = i+1; j < objc; j++) 
			coll.handle(get_obj(i), get_obj(j));

}

void World::add_obj(Object obj) {

	objects.push_back(obj);

	objc++;

}

Object *World::get_obj(int id) {

	return &objects.at(id);
}

Object World::copy_obj(int id) {

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
