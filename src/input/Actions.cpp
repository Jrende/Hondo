#include <set>
#include <iostream>
#include <GLFW/glfw3.h>
#include "Actions.hpp"

namespace Actions {
  namespace {
    std::set<int> repeatables({
	Actions::Forward,
	Actions::Backward,
	Actions::Left,
	Actions::Right,
	Actions::Up,
	Actions::Down
	});
  }
  int Forward = GLFW_KEY_W;
  int Backward = GLFW_KEY_S;
  int Left = GLFW_KEY_A;
  int Right = GLFW_KEY_D;
  int Up = GLFW_KEY_SPACE;
  int Down = GLFW_KEY_LEFT_SHIFT;

  bool is_repeatable(int action) {
    return repeatables.count(action) > 0;
  }

  void set_repeatable(int action) {
    repeatables.insert(action);
  }
}
