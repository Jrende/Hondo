#include <string>
#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <sstream>
#include "ecs/World.hpp"
#include "ecs/Component.hpp"
#include "ecs/Bag.hpp"
struct TestComp: Component<TestComp> {
  std::string s;
  TestComp(std::string s): s(s) {};
};
struct OtherComp: Component<OtherComp> {
  std::string s, s2, s3, s4;
  OtherComp(std::string s):
    s(s),
    s2(s),
    s3(s),
    s4(s)
  {};
};

int main(int argc, char** argv) {
  /*
  Bag bag;
  bag.init<TestComp>();
  bag.allocate<TestComp>(50, "Hej");
  Bag bag2 = bag;
  std::cout << "test: " << bag2.get_component_for_entity<TestComp>(50)->s << "\n";
  */
  World world;
  Entity root = world.create_entity();
  root.add_component<TestComp>("Hej hej");
  auto comp = root.get_component<TestComp>();
  std::cout << "TestComp: " << comp->s << '\n';
  root.add_component<OtherComp>("Other Comp");
  std::cout << "TestComp: " << comp->s << '\n';
  auto other = root.get_component<OtherComp>();
  std::cout << "OtherComp: " << other->s << '\n';
  /*
  test_comp->s = "Changed!";
  world.process();

  for(int i = 0; i < 50; i++) {
    Entity root = world.create_entity();
    root.add_component<TestComp>("Hej hej");
    Entity root2 = world.create_entity();
    root2.add_component<OtherComp>("Othercomp");
  }

  auto test_comp2 = root.get_component<TestComp>();
  std::cout << "test_comp: " << test_comp2->s << '\n';

  auto other_comp = root.get_component<OtherComp>();
  std::cout << "other_comp: " << other_comp->s3 << '\n';
  */
  return 0;
}
