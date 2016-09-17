#include "Octree.hpp"
#define GLM_FORCE_RADIANS
#include <glm/gtx/rotate_vector.hpp>
void Octree::add_aabb(Entity entity, const AABB& aabb) {
  for(const auto& p: aabb.cube) {
    add_point(entity.get_id(), p);
  }
}

void Octree::add_point(int entity_id, const glm::vec3& point) {
  root.add_point(entity_id, point);
}

bool Octree::contains_point(const glm::vec3& point) {
  return root.contains_point(point);
}

std::vector<int> Octree::get_items_in_frustum(const Frustum& frustum) {
  std::vector<int> entities;
  root.get_points_in_frustum(frustum, entities);
  return entities;
}

bool Octree::Node::contains_point(const glm::vec3& p) {
  return 
    p.x < (pos.x + half_size.x) && p.x > (pos.x - half_size.x) &&
    p.y < (pos.y + half_size.y) && p.y > (pos.y - half_size.y) &&
    p.z < (pos.z + half_size.z) && p.z > (pos.z - half_size.z);
}

int Octree::Node::get_octant(const glm::vec3& point) const {
  int oct = 0;
  if(point.x >= pos.x) oct |= 4;
  if(point.y >= pos.y) oct |= 2;
  if(point.z >= pos.z) oct |= 1;
  return oct;
}

void Octree::Node::convert_to_interior() {
  assert(children == nullptr);
  assert(point != nullptr);

  children = std::make_unique<std::array<Node, 8>>();
  for(int i = 0; i < 8; i++) {
    glm::vec3 newOrigin = pos;
    newOrigin.x += half_size.x * (i&4 ? .5f : -.5f);
    newOrigin.y += half_size.y * (i&2 ? .5f : -.5f);
    newOrigin.z += half_size.z * (i&1 ? .5f : -.5f);
    (*children)[i] = Node(newOrigin, half_size / 2.0f);
    (*children)[i].tree = tree;
  }
  auto old_entity_id = entity_id;
  entity_id = -1;
  (*children)[get_octant(*point)].add_point(old_entity_id, *point);

  point = nullptr;
}

/*
 * Three cases:
 *  Node is interior
 *    Insert to appropriate node
 *  Node is leaf with no data
 *    Found correct node!
 *  Node is leaf with data
 *    Convert leaf to interior, add points to correct leafs
 */
void Octree::Node::add_point(int entity_id, const glm::vec3& point) {
  if(!tree->contains_point(point)) {
    return;
  }
  //Probably not the best way to do it
  if(half_size.x < 1) {
    return;
  }
  if(children == nullptr) {
    if(this->entity_id == -1) {
      this->entity_id = entity_id;
      this->point = std::make_unique<glm::vec3>(point);
    } else {
      convert_to_interior();
      (*children)[get_octant(point)].add_point(entity_id, point);
    }
  } else {
    (*children)[get_octant(point)].add_point(entity_id, point);
  }
}

  void Octree::Node::get_points_in_frustum(const Frustum& frustum, std::vector<int>& result) {
  if(is_contained_by_frustum(frustum)) {
    if(children != nullptr) {
      for(auto& child: *children) {
        child.get_points_in_frustum(frustum, result);
      }
    } else {
      if(point != nullptr) {
        result.push_back(entity_id);
      }
    }
  }
}

bool Octree::Node::is_contained_by_frustum(const Frustum& f) {
  if(point == nullptr) {
    return false;
  }
  const auto& p = *point;
  float d1 = glm::dot(glm::cross(f.ntl, f.ntr), p - f.ntl);
  return d1 > 0;
}
