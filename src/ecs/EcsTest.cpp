#include <string>
#include <array>
#include "Bag.hpp"
struct Test {
  int f;
  std::string s;
  Test(std::string s, int f): s(s), f(f) {};
  //int s;
  //Test(): f(count++), s("") {}
};
const int size = 4;
int main(int argc, char** argv) {
  Bag bag;
  bag.init<Test>();
  for(int i = 0; i < size; i++) {
    Test* t = bag.allocate<Test>("it works!", 100 + i);
  }

  bag.free_obj(bag.get<Test>(1));
  Test* t = bag.allocate<Test>("New item", 200);
  for(auto i = bag.begin<Test>(), end = bag.end<Test>(); i != end; i++) {
    const Test& t = *i;
    std::cout << t.f << ": " << t.s << std::endl;
  }

  return 0;
}
