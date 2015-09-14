#pragma once
#include <unordered_map>
class Entity {
  protected:
    int id;
  public:
    Entity(int id): id(id) {};

    int get_id() const {
      return id;
    }

    bool operator!=(const Entity& other) const {
      return !(*this == other);
    }

    bool operator==(const Entity& other) const {
      return other.id == this->id;
    }
};
