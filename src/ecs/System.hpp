#pragma once
#include <vector>
#include "World.hpp"
template<typename F, typename... C>
class System {
  private:
    F function;
    World& world;

  public:
    //F: [](std::vector<Entity> entities, World& world){}
    System(F&& function, World& world): function(function), world(world) {}

    void process_entities(std::vector<Entity> entities) {
      function(entities, world);
    }
};
