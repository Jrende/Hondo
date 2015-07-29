#pragma once
template<class T>
class EntityManager {
  private:
    struct Node {
      Entity entity;
      Node* parent = nullptr;
      std::vector<Node> children;
      Node();
    };
    static int last_id = 0;
    EntityManager::Node root;
    std::vector<Entity> flat_list;
    unsigned int fetch_render_object_id(const Entity& entity);
    boost::optional<EntityManager::Node&> find_node(const Entity& entity);
    boost::optional<EntityManager::Node&> find_node_from(EntityManager::Node& start_node, const Entity& entity);
  public:
    Entity create_entity();
    Entity create_entity(const Entity& parent);
};
