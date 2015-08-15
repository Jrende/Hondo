#pragma once
#include <vector>
#include <boost/optional.hpp>
#include "Entity.hpp"
class EntityManager {
  private:
    struct Node {
      const Entity& entity;
      Node* parent = nullptr;
      std::vector<Node> children;
      Node(const Entity& entity): entity(entity) {};
    };
    EntityManager::Node root;
    std::vector<Entity> flat_list;
    unsigned int fetch_render_object_id(const Entity& entity);
    boost::optional<EntityManager::Node&> find_node(Entity& entity);
    boost::optional<EntityManager::Node&> find_node_from(EntityManager::Node& start_node, const Entity& entity);
    Entity new_entity();
  public:
    Entity create_entity();
    Entity create_entity(const Entity& parent);
    EntityManager();
};
