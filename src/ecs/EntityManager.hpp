#pragma once
#include <vector>
#include <boost/optional.hpp>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
template<class Entity>
class EntityManager {
  typedef int component_id;
  private:
    struct Node {
      const Entity& entity;
      Node* parent = nullptr;
      std::vector<Node> children;
      Node(const Entity& entity): entity(entity) {};
    };
    Node root;
    //unsigned int fetch_render_object_id(const Entity& entity);

    Entity new_entity() {
      static int last_id = 0;
      return Entity(last_id++);
    }

    boost::optional<Node&> find_node(Entity& entity) {
      return find_node_from(root, entity);
    }

    boost::optional<Node&> find_node_from(Node& start_node, const Entity& entity) {
      if(start_node.entity == entity) {
        return boost::optional<Node&>(start_node);
      }
      for(Node& child: start_node.children) {
        if(boost::optional<Node&> result = find_node_from(child, entity))
          return result;
      }
      return boost::none;
    }


    //std::unordered_map<Entity, std::unordered_set<component_id>> entity_components;
  public:

    EntityManager(): root(new_entity()) {
      std::cout << "Construct EntityManager\n";
    }

    Entity create_entity() {
      return create_entity(root.entity);
    }

    Entity create_entity(const Entity& parent) {
      Node node(new_entity());
      if(boost::optional<Node&> result = find_node_from(root, parent)) {
        node.parent = &root;
        root.children.push_back(node);
        (*result).children.push_back(node);
      }
      return node.entity;
    }
};
