#include <string>
#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <sstream>
#include "ecs/World.hpp"
#include "ecs/Component.hpp"
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
  World world;
  Entity root = world.create_entity();
  world.add_component<TestComp>(root, "Hej hej");
  world.add_component<OtherComp>(root, "Other Comp");
  auto test_comp = world.get_component<TestComp>(root);
  std::cout << "test_comp: " << test_comp->s << '\n';
  test_comp->s = "Changed!";
  world.process();

  for(int i = 0; i < 50; i++) {
    Entity root = world.create_entity();
    world.add_component<TestComp>(root, "Hej hej");
    Entity root2 = world.create_entity();
    world.add_component<OtherComp>(root2, "Othercomp");
  }

  auto test_comp2 = world.get_component<TestComp>(root);
  std::cout << "test_comp: " << test_comp2->s << '\n';

  auto other_comp = world.get_component<OtherComp>(root);
  std::cout << "other_comp: " << other_comp->s3 << '\n';
  return 0;
}
