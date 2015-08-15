#pragma once
#include <array>
#include <unordered_map>
#include <boost/optional.hpp>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
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
    template<typename C, typename... Rest>
    void add_component(const Entity& e, Rest... rest) {
      component_manager.add_component<C>(e, std::forward<Rest>(rest)...);
    }

    template<class C>
    ComponentManager::Ref<C> get_component(const Entity& e) {
      return component_manager.get_component_ref<C>(e);
    }

    void process();
};
