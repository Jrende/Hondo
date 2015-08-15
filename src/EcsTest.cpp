#include <string>
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
int main(int argc, char** argv) {
  World world;
  Entity root = world.create_entity();
  world.add_component<TestComp>(root, "Hej hej");
  auto test_comp = world.get_component<TestComp>(root);
  std::cout << "test_comp: " << test_comp->s << '\n';
  test_comp->s = "Changed!";
  world.process();
  test_comp = world.get_component<TestComp>(root);
  std::cout << "test_comp: " << test_comp->s << '\n';

}
