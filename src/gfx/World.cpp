#include "World.hpp"
World::World():
  render_list(),
  id_to_list_index(),
  scene_graph(render_list, id_to_list_index)
{
}

Entity create_new_entity() {
  static int last_id = 0;
  return Entity(last_id++);
}

void World::add_render_object(RenderObject&& obj) {
  render_list.push_back(obj);
  id_to_list_index[obj.entity] = render_list.size() - 1;
}

Entity World::create_empty_entity() {
  Entity e = create_new_entity();
  scene_graph.add_entity(e);
  return e;
}

Entity World::create_empty_entity(Entity parent) {
  Entity e = create_new_entity();
  scene_graph.add_entity(parent);
  return e;
}

Entity World::create_entity(RenderObject&& obj) {
  Entity e = create_empty_entity();
  obj.entity = e;
  add_render_object(std::move(obj));
  return e;
}

Entity World::create_entity(Entity parent, RenderObject&& obj) {
  Entity e = create_empty_entity(parent);
  obj.entity = e;
  add_render_object(std::move(obj));
  return e;
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
