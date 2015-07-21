#include "World.hpp"
World::World():
  render_list(),
  id_to_list_index(),
  scene_graph(render_list, id_to_list_index)
{
}

void World::add_render_object(RenderObject&& obj) {
  render_list.push_back(obj);
  id_to_list_index[obj.entity] = render_list.size() - 1;
}

Entity World::create_entity() {
  return scene_graph.create_entity();
}

Entity World::create_entity(Entity parent) {
  return scene_graph.create_entity(parent);
}

Entity World::create_entity(RenderObject&& obj) {
  render_list.push_back(obj);
  id_to_list_index[obj.entity] = render_list.size() - 1;
  return scene_graph.create_entity(std::move(obj));
}

Entity World::create_entity(Entity parent, RenderObject&& obj) {
  render_list.push_back(obj);
  id_to_list_index[obj.entity] = render_list.size() - 1;
  return scene_graph.create_entity(parent, std::move(obj));
}

void World::translate(Entity entity, const glm::vec3& pos) {
  scene_graph.translate(entity, pos);
}

void World::scale(Entity entity, const glm::vec3& scale) {
  scene_graph.scale(entity, scale);
}

void World::rotate(Entity entity, float angle, const glm::vec3& axis) {
  scene_graph.rotate(entity, angle, axis);
}
