#include <string>
#include <algorithm>
#include <array>
#include <vector>
#include <sstream>
#include "ecs/Bag.hpp"
#include "ecs/Entity.hpp"
#include "ecs/Component.hpp"
struct TestComp: Component<TestComp> {
  std::string s;
  TestComp(std::string s): s(s){};
};

const int size = 4;
int main(int argc, char** argv) {
  Bag bag;
  bag.init<TestComp>();
  std::vector<Entity> ents;
  for(int i = 0; i < size; i++) {
    Entity e(i);
    ents.push_back(e);
    std::stringstream ss;
    ss << "TestComp for entity " << i << "!";
    TestComp* t = bag.allocate<TestComp>(e, ss.str());
  }

  bag.free_obj(bag.get<TestComp>(1));
  const auto& it = std::find(ents.begin(), ents.end(), Entity(1));
  ents.erase(it);
  TestComp* t = bag.allocate<TestComp>(Entity(4), "TestComp for entity 4!");
  ents.push_back(Entity(4));

  for(const auto& e: ents) {
    int i = e.get_id();
    TestComp* c = bag.get_component_for_entity<TestComp>(i);
    if(i != c->get_entity_id()) {
      std::cerr << "Entity ID not same as component entity id!\n";
    }

  }

  return 0;
}
