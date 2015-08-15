#pragma once
#include <unordered_map>
class Bag;
class Entity {
  friend Bag;
  private:
    unsigned int id;
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
};
