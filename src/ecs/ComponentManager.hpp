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
        unsigned int entity_id;
        Bag* bag = nullptr;
        ComponentManager* component_manager = nullptr;
      
      public:
        Ref(unsigned int entity_id, ComponentManager* component_manager): entity_id(entity_id), component_manager(component_manager) {
        };

        C* operator->() {
          if(bag == nullptr || bag->is_null()) {
            bag = &component_manager->components[C::type_id];
          }
          return bag->get_component_for_entity<C>(entity_id);
        }

        bool operator==(const Ref& other) {
          return other.entity.id == this->entity_id;// && other->component.id == this->component.id;
        }
    };

  private:
    //Index of vector corresponds to component type id
    std::vector<Bag> components;
    std::vector<std::unordered_set<int>> changed_components;
    
    //ie entity_to_component_index[Transform::id][entity.id] will give the index of the entitys transform component
  public:
    ComponentManager(): components(1)
  {
    //init refs set
  }

    template<typename C, typename... Rest>
    void add_component(unsigned int e, Rest&&... args) {
      //Try using bag.at & exceptions, benchmark
      int id = Component<C>::type_id;
      int prev = components.size();
      if(id >= prev) {
        std::cout << "Resize components\n";
        components.resize(id + 1);
      }
      Bag& bag = components[Component<C>::type_id];
      if(components[id].size() == 0) {
        bag.init<C>();
      }

      C* c = bag.allocate<C>(e, std::forward<Rest>(args)...);
      c->id = last_component_id++;
    }

    template<typename C>
    ComponentManager::Ref<C> get_component_ref(unsigned int e) {
      return ComponentManager::Ref<C>(e, this);
    }

    void clear() {
      //changed_components.clear();
    }
};
