#pragma once
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <vector>
#include "Component.hpp"
#include "Bag.hpp"
static int last_component_id = 0;
class ComponentManager {
  typedef int component_type;
  typedef int c_index;
  typedef int e_id;

  template<typename C>
    class Ref {
      friend ComponentManager;
      private:
        Entity entity;
        Bag* bag = nullptr;
      
      public:
        Ref(Entity entity, Bag* bag): entity(entity), bag(bag) {
        };

        C* operator->() {
          return bag->get_component_for_entity<C>(entity);
        }

        bool operator==(const Ref& other) {
          return other.entity.id == this->entity.id && other.component.id == this->component.id;
        }
    };

  private:
    //Index of vector corresponds to component type id
    std::vector<Bag> components;
    std::vector<std::unordered_set<int>> changed_components;
    
    //ie entity_to_component_index[Transform::id][entity.id] will give the index of the entitys transform component
  public:
    ComponentManager():
      components(ComponentId::max_component_id),
      changed_components(ComponentId::max_component_id)
  {
    //init refs set
  }

    template<typename C, typename... Rest>
    void add_component(const Entity& e, Rest&&... args) {
      //Try using bag.at & exceptions, benchmark
      if(components[Component<C>::type_id].size() == 0) {
        Bag& bag = components[Component<C>::type_id];
        bag.init<C>();
      }

      Bag& bag = components[Component<C>::type_id];

      C* c = bag.allocate<C>(e, std::forward<Rest>(args)...);
      c->id = last_component_id++;
    }

    template<typename C>
    ComponentManager::Ref<C> get_component_ref(const Entity& e) {
      Bag* bag = &components[Component<C>::type_id];
      return ComponentManager::Ref<C>(Entity(e), bag);
    }

    void clear() {
      changed_components.clear();
    }
};
