#include "World.hpp"
World::World() {
}

Entity World::create_entity() {
  return entity_manager.create_entity();
}

Entity World::create_entity(const Entity& parent) {
  return entity_manager.create_entity(parent);
}

void World::process() {
}
