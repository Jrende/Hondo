#pragma once
#include <unordered_map>
class Entity {
  private:
  public:
    unsigned int id = -1;

    Entity() { }
    Entity(int id): id(id) { }

    bool operator!=(const Entity& other) const {
      return !(*this == other);
    }

    bool operator==(const Entity& other) const {
      return other.id == this->id;
    }

    template<class Component>
    Entity& add_component(Component component)

    template<class Component>
    Ref<Component> get_component()
};
