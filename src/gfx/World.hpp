#pragma once
#include <array>
#include <unordered_map>
#include <boost/optional.hpp>
#include "SceneGraph.hpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
//ZA WARUDO
class World {
  friend class Renderer;
  private:
    std::vector<RenderObject> render_list;
    std::unordered_map<Entity, unsigned int> id_to_list_index;
    SceneGraph scene_graph;
    void add_render_object(RenderObject&& obj);
  public:
    World();
    Entity create_entity();
    Entity create_entity(Entity parent);
    Entity create_entity(RenderObject&& obj);
    Entity create_entity(Entity parent, RenderObject&& obj);
    void translate(Entity entity, const glm::vec3& pos);
    void scale(Entity entity, const glm::vec3& scale);
    void rotate(Entity entity, float angle, const glm::vec3& axis);
};