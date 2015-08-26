#pragma once
class Bag;
class ComponentManager;
template<class T>
class Component {
  friend Bag;
  friend ComponentManager;
  private:
    unsigned int id;
    unsigned int entity_id;
  public:
    static int const type_id;
    int get_id() const { 
      return id;
    }

    int get_entity_id() const { 
      return entity_id;
    }
};

namespace ComponentId {
  extern int max_component_id;
}

template <class T>
const int Component<T>::type_id = ComponentId::max_component_id++;
