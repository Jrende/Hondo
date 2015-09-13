#pragma once
#include <unordered_map>
class Entity {
  protected:
  public:
    int id;
    Entity(int id): id(id) {};

    bool operator!=(const Entity& other) const {
      return !(*this == other);
    }

    bool operator==(const Entity& other) const {
      return other.id == this->id;
    }
};
