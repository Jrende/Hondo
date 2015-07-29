#include "EntityManager.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

bool operator==(const RenderObject& render_object, const Entity& entity) {
  return render_object.entity == entity;
}

boost::optional<EntityManager::Node&> EntityManager::find_node(const Entity& entity) {
  return find_node(root, entity);
}

boost::optional<EntityManager::Node&> EntityManager::find_node_from(EntityManager::Node& start_node, const Entity& entity) {
  if(start_node.entity == entity) {
    return start_node;
  }
  for(Node& child: start_node.children) {
    if(boost::optional<EntityManager::Node&> result = find_node(child, entity))
      return result;
  }
  return boost::none;
}

Entity EntityManager::alloc_entity() {
  return Entity(last_id++);
}

Entity EntityManager::create_entity() {
  return create_entity(root.entity);
}

Entity EntityManager::create_entity(Entity parent) {
  EntityManager::Node node;
  if(boost::optional<EntityManager::Node&> result = find_node(root, parent)) {
    node.entity = alloc_entity();
    node.parent = &root;
    root.children.push_back(node);
    (*result).children.push_back(node);
  }
  return node.entity;
}
