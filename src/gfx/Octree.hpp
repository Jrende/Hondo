#pragma once
#include "AABB.hpp"
#include <array>
#include <memory>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "Entity.hpp"
#include <unordered_set>

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

      bool contains_point(const glm::vec3& p) {
        return 
          p.x < (pos.x + half_size.x) && p.x > (pos.x - half_size.x) &&
          p.y < (pos.y + half_size.y) && p.y > (pos.y - half_size.y) &&
          p.z < (pos.z + half_size.z) && p.z > (pos.z - half_size.z);
      }

      int get_octant(const glm::vec3& point) const {
        int oct = 0;
        if(point.x >= pos.x) oct |= 4;
        if(point.y >= pos.y) oct |= 2;
        if(point.z >= pos.z) oct |= 1;
        return oct;
      }

      void convert_to_interior() {
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
      void add_point(int entity_id, const glm::vec3& point) {
        if(!tree->contains_point(point)) {
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
    };

    Node root;

    void add_point(int entity_id, const glm::vec3& point);

  public:
    Octree(): root(Node(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1000.0f, 1000.0f, 1000.0f)))
    {
      root.tree = this;
    }
    bool contains_point(const glm::vec3& point);
    void add_aabb(Entity entity, const AABB& r_obj);
    std::unordered_set<int> get_items_in_frustum();
};
