#pragma once
#include <unordered_map>
class ComponentManager {
  typedef int c_id;
  typedef int c_index;
  typedef int e_id;
  private:
    std::unordered_map<c_id, Bag> components;
    std::unordered_map<c_id, std::unordered_map<e_id, c_index>> entity_to_component_index;
    //ie entity_to_component_index[Transform::id][entity.id] will give the index of the entitys transform component
  public:
};
