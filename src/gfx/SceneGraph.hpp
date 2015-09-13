#pragma once
#include <vector>
#include <unordered_map>
#include <boost/optional.hpp>
#include "Entity.hpp"
#include "RenderObject.hpp"
#include "Transform.hpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace std {
  template <>
    struct hash<Entity> {
      std::size_t operator()(const Entity& k) const {
        return k.id;
      }
    };
};

class SceneGraph {
  struct Node {
    Node* parent = nullptr;
    std::vector<Node> children;
    SceneGraph* graph;
    Transform effective_transform;
    Transform node_transform;
    Entity entity;
    bool has_render_object = true;

    void update(const Transform& parent_matrix);
    void update();

    Node(Entity entity);
  };

  private:
    std::vector<RenderObject>& render_list;
    std::unordered_map<Entity, unsigned int>& id_to_list_index;

    SceneGraph::Node root = SceneGraph::Node(Entity(-1));
    unsigned int fetch_render_object_id(const Entity& entity);
    void update_transform(const RenderObject& render_object);
    boost::optional<SceneGraph::Node&> find_node(const Entity& entity);
    boost::optional<SceneGraph::Node&> find_node(SceneGraph::Node& node, const Entity& entity);
  public:
    SceneGraph(
      std::vector<RenderObject>& render_list,
      std::unordered_map<Entity, unsigned int>& id_to_list_index
    );
    RenderObject& get_render_object(Entity entity);
    Transform& transform(Entity entity);
    void translate(Entity entity, const glm::vec3& pos);
    void scale(Entity entity, const glm::vec3& scale);
    void rotate(Entity entity, float angle, const glm::vec3& axis);
    void add_entity(Entity entity);
    void add_entity(Entity parent, Entity entity);
};

