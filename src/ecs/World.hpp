#pragma once
#include <array>
#include <boost/optional.hpp>
#define GLM_FORCE_RADIANS
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
//ZA WARUDO
class World {
  public:
  class Entity {
    friend World;
    private:
      unsigned int id;
      World* world = nullptr;
    public:
      Entity(int id): id(id) { }

      bool operator!=(const Entity& other) const {
        return !(*this == other);
      }

      bool operator==(const Entity& other) const {
        return other.id == this->id;
      }

      int get_id() const {
        return id;
      }

      template<typename C, typename... Rest>
      void add_component(Rest... rest) {
        world->add_component<C>(*this, std::forward<Rest>(rest)...);
      }

      template<typename C>
      ComponentManager::Ref<C> get_component() {
        return world->get_component<C>(*this);
      }
  };
    World() {}

    Entity create_entity() {
      auto e = entity_manager.create_entity();
      e.world = this;
      return e;
    }

    Entity create_entity(const Entity& parent) {
      auto e = entity_manager.create_entity(parent);
      e.world = this;
      return e;
    }

    template<typename C, typename... Rest>
    void add_component(const Entity& e, Rest... rest) {
      component_manager.add_component<C>(e.id, std::forward<Rest>(rest)...);
    }

    template<typename C>
    ComponentManager::Ref<C> get_component(const Entity& e) {
      return component_manager.get_component_ref<C>(e.id);
    }

    void process();
  private:
    EntityManager<Entity> entity_manager;
    ComponentManager component_manager;
    
};
typedef World::Entity Entity;

