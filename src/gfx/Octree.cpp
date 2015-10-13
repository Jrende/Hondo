#include "Octree.hpp"
void Octree::add_aabb(Entity entity, const AABB& aabb) {
  for(const auto& p: aabb.cube) {
    add_point(entity.get_id(), p);
  }
}

void Octree::add_point(int entity_id, const glm::vec3& point) {
  root.add_point(entity_id, point);
}

std::unordered_set<int> Octree::get_items_in_frustum() {
  return std::unordered_set<int>();
}
