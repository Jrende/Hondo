#pragma once
#include <array>
#include <unordered_map>
#include <boost/optional.hpp>
#include "SceneGraph.hpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
//ZA WARUDO
class World {
  private:
    EntityManager entity_manager;
    ComponentManager component_manager;
    
  public:
    World();
    Entity create_entity();
    Entity create_entity(const Entity& parent);
    template<class System>
    void add_system();
};
