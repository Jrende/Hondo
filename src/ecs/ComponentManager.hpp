#pragma once
#include <unordered_map>
#include <unordered_set>
#include <list>
#include "Component.hpp"
#include "Bag.hpp"
static int last_component_id = 0;
class ComponentManager {
  typedef int component_type;
  typedef int c_index;
  typedef int e_id;

  template<typename C>
    class Ref {
      private:
        bool is_dirty = true;
        C* comp = nullptr;

        Entity entity;
        Bag* bag;
        ComponentManager* component_manager;
      
      public:
        Ref(Entity entity, Bag* bag, ComponentManager* component_manager): entity(entity), bag(bag), component_manager(component_manager) {};

        C* operator->() {
          if(is_dirty) {
            comp = bag->get_component_for_entity<C>(entity);
            is_dirty = false;
          }
          if(comp != nullptr) {
            //Try not to do this only once every frame
            component_manager->changed_components[C::type_id].insert(comp->get_id());
          }
          return comp;
        }
    };

  private:
    std::unordered_map<component_type, Bag> components;
    std::unordered_map<component_type, std::unordered_set<int>> changed_components;
    //ie entity_to_component_index[Transform::id][entity.id] will give the index of the entitys transform component
  public:
    template<typename C, typename... Rest>
    void add_component(const Entity& e, Rest... args) {
      //Try using bag.at & exceptions, benchmark
      if(components.count(Component<C>::type_id) == 0) {
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
      return ComponentManager::Ref<C>(Entity(e), bag, this);
    }
};
