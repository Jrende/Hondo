#include "SceneGraph.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
/*
bool operator==(const RenderObject& render_object, const Entity& entity) {
  return render_object.entity == entity;
}

SceneGraph::SceneGraph(
    std::vector<RenderObject>& render_list,
    std::unordered_map<Entity, unsigned int>& id_to_list_index
    ):
  render_list(render_list),
  id_to_list_index(id_to_list_index)
{
  root.has_render_object = false;
}

SceneGraph::Node::Node():
  effective_transform(),
  node_transform() { }

//RS
void SceneGraph::Node::update() {
  Transform t;
  if(parent != nullptr) {
    t = parent->effective_transform;
  }
  update(t);
}

void SceneGraph::Node::update(const Transform& parent_transform) {
  Transform t = parent_transform;
  t.translate(node_transform.get_pos());
  t.scale(node_transform.get_scale());
  t.rotate(node_transform.get_rot());

  effective_transform = t;
  if(has_render_object) {
    auto& render_object = graph->get_render_object(entity);
    render_object.transform.model_matrix = t.model_matrix;
    render_object.aabb.transform(render_object.transform.model_matrix);
  }
  for(auto& child: children) {
    child.update(t);
  }
}

unsigned int SceneGraph::fetch_render_object_id(const Entity& entity) {
  if(id_to_list_index.count(entity) == 0 || render_list[id_to_list_index[entity]].entity != entity) {
    unsigned int it = std::find_if(render_list.begin(), render_list.end(), [&](const RenderObject& r_obj)->bool {
      return r_obj.entity == entity;
    }) - render_list.begin();
    if(it != render_list.size()) {
      id_to_list_index[entity] = it;
    }
  }
  unsigned int index = id_to_list_index[entity];
  return index;
}


RenderObject& SceneGraph::get_render_object(Entity entity) {
  return render_list[fetch_render_object_id(entity)];
}

Transform& SceneGraph::transform(Entity entity) {
  return render_list[fetch_render_object_id(entity)].transform;
}

void SceneGraph::translate(Entity entity, const glm::vec3& pos){
  if(boost::optional<SceneGraph::Node&> node = find_node(entity)) {
    node->node_transform.translate(pos);
    root.update();
  }
}

void SceneGraph::scale(Entity entity, const glm::vec3& scale){
  if(boost::optional<SceneGraph::Node&> node = find_node(entity)) {
    node->node_transform.scale(scale);
    root.update(root.node_transform);
  }
}

void SceneGraph::rotate(Entity entity, float angle, const glm::vec3& axis){
  if(boost::optional<SceneGraph::Node&> node = find_node(entity)) {
    node->node_transform.rotate(angle, axis);
    root.update();
  }
}

boost::optional<SceneGraph::Node&> SceneGraph::find_node(const Entity& entity) {
  return find_node(root, entity);
}

boost::optional<SceneGraph::Node&> SceneGraph::find_node(SceneGraph::Node& node, const Entity& entity) {
  if(node.entity == entity) {
    return node;
  }
  for(Node& child: node.children) {
    if(boost::optional<SceneGraph::Node&> result = find_node(child, entity))
      return result;
  }
  return boost::none;
}

Entity SceneGraph::create_entity() {
  return create_entity(root.entity);
}

Entity SceneGraph::create_entity(Entity parent) {
  SceneGraph::Node node;
  node.graph = this;
  node.parent = &root;
  root.children.push_back(node);
  if(boost::optional<SceneGraph::Node&> result = find_node(root, parent)) {
    (*result).children.push_back(node);
  }
  return node.entity;
}

Entity SceneGraph::create_entity(RenderObject&& obj) {
  return create_entity(root.entity, std::move(obj));
}

Entity SceneGraph::create_entity(Entity parent, RenderObject&& obj) {
  SceneGraph::Node node;
  node.graph = this;
  node.entity = obj.entity;

  if(boost::optional<SceneGraph::Node&> result = find_node(parent)) {
    node.parent = &(*result);
    result->children.push_back(node);
  }
  return node.entity;
}
*/
