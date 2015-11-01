#pragma once
#include <vector>
#include "World.hpp"

template<typename... C>
class System {
  private:
    World& world;

  public:
    //F: [](std::vector<Entity> entities, World& world){}
    System(World& world): world(world) {}

    //void process_entities(std::vector<Entity> entities) {
      //function(entities, world);
    //}
};
