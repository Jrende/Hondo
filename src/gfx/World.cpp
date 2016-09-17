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

void World::add_render_object(RenderObject obj) {
  render_list.push_back(obj);
  id_to_list_index[obj.entity] = render_list.size() - 1;
}

void World::rebuild_octree() {
  octree = Octree{};
  for(auto render_object: render_list) {
    render_object.update_aabb();
    octree.add_aabb(render_object.entity, render_object.aabb);
  }
}

RenderObject& World::get_render_object(Entity entity) {
  return render_list[id_to_list_index[entity.get_id()]];
}

Entity World::create_empty_entity() {
  Entity e = create_new_entity();
  scene_graph.add_entity(e);
  return e;
}

Entity World::create_empty_entity(Entity parent) {
  Entity e = create_new_entity();
  scene_graph.add_entity(parent, e);
  return e;
}

Entity World::create_entity(RenderObject obj) {
  Entity e = create_empty_entity();
  obj.entity = e;
  add_render_object(std::move(obj));
  octree.add_aabb(e, get_render_object(e).aabb);
  return e;
}

Entity World::create_entity(Entity parent, RenderObject obj) {
  Entity e = create_empty_entity(parent);
  obj.entity = e;
  add_render_object(std::move(obj));
  octree.add_aabb(e, get_render_object(e).aabb);
  return e;
}

void World::translate(Entity entity, const glm::vec3& pos) {
  scene_graph.translate(entity, pos);
  rebuild_octree();
}

void World::scale(Entity entity, const glm::vec3& scale) {
  scene_graph.scale(entity, scale);
  rebuild_octree();
}

void World::rotate(Entity entity, float angle, const glm::vec3& axis) {
  scene_graph.rotate(entity, angle, axis);
  rebuild_octree();
}

std::vector<RenderObject> World::get_visible_objects(const Frustum& frustum) {
  const std::vector<int>& list = octree.get_items_in_frustum(frustum);
  std::vector<RenderObject> render_objects;
  for(const auto& item: list) {
    render_objects.push_back(render_list[id_to_list_index[item]]);
  }
  return render_objects;
}
