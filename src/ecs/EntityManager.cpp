#include "EntityManager.hpp"
#include <iostream>

EntityManager::EntityManager(): root(new_entity()) {
  std::cout << "Construct EntityManager\n";
}

boost::optional<EntityManager::Node&> EntityManager::find_node(Entity& entity) {
  return find_node_from(root, entity);
}

boost::optional<EntityManager::Node&> EntityManager::find_node_from(EntityManager::Node& start_node, const Entity& entity) {
  if(start_node.entity == entity) {
    return boost::optional<EntityManager::Node&>(start_node);
  }
  for(Node& child: start_node.children) {
    if(boost::optional<EntityManager::Node&> result = find_node_from(child, entity))
      return result;
  }
  return boost::none;
}

static int last_id = 0;
Entity EntityManager::new_entity() {
  return Entity(last_id++);
}

Entity EntityManager::create_entity() {
  return create_entity(root.entity);
}

Entity EntityManager::create_entity(const Entity& parent) {
  EntityManager::Node node(new_entity());
  if(boost::optional<EntityManager::Node&> result = find_node_from(root, parent)) {
    node.parent = &root;
    root.children.push_back(node);
    (*result).children.push_back(node);
  }
  return node.entity;
}
