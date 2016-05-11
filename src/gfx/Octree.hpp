#pragma once
#include "AABB.hpp"
#include <array>
#include <memory>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "Entity.hpp"
#include <unordered_set>
//#include "OctreeNode.hpp"
#include <vector>

class Octree {
  friend class DebugRenderer;
  private:
  struct Node {
    Octree* tree;
    std::unique_ptr<std::array<Node, 8>> children = nullptr;
    std::unique_ptr<glm::vec3> point = nullptr;
    int entity_id = -1;

    glm::vec3 pos, half_size;

    Node():
      pos(0, 0, 0), half_size(1, 1, 1)
    {}
    Node(glm::vec3 pos, glm::vec3 half_size):
      pos(pos), half_size(half_size)
    {}

    bool contains_point(const glm::vec3& p);

    int get_octant(const glm::vec3& point) const;

    void convert_to_interior();

    /*
     * Three cases:
     *  Node is interior
     *    Insert to appropriate node
     *  Node is leaf with no data
     *    Found correct node!
     *  Node is leaf with data
     *    Convert leaf to interior, add points to correct leafs
     */
    void add_point(int entity_id, const glm::vec3& point);
  };

  Node root;

  void add_point(int entity_id, const glm::vec3& point);

  public:
  Octree(): root(Node(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1024.0f, 1024.0f, 1024.0f)))
  {
    root.tree = this;
  }
  bool contains_point(const glm::vec3& point);
  void add_aabb(Entity entity, const AABB& r_obj);
  std::vector<int> get_items_in_frustum(
      const glm::vec3& ntl,
      const glm::vec3& ntr,
      const glm::vec3& nbl,
      const glm::vec3& nbr,
      const glm::vec3& ftl,
      const glm::vec3& ftr,
      const glm::vec3& fbl,
      const glm::vec3& fbr
      );
};
