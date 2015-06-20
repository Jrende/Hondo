#pragma once
#include <unordered_map>
class Entity {
  private:
  public:
    unsigned int id;
    Entity();

    bool operator!=(const Entity& other) const {
      return !(*this == other);
    }

    bool operator==(const Entity& other) const {
      return other.id == this->id;
    }
};
