#ifndef __HONDO_INPUT_H__
#define __HONDO_INPUT_H__
#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Action.h"
namespace Input {
  typedef int Key;
  typedef std::function<void()> ActionHandler;
  namespace {
    std::unordered_map< Action, std::vector<ActionHandler> > handlers;
    std::unordered_map<Key, Action> mappings = {
      {GLFW_KEY_W, Action::Forward},
      {GLFW_KEY_S, Action::Backward},
      {GLFW_KEY_A, Action::Left},
      {GLFW_KEY_D, Action::Right},
      {GLFW_KEY_Q, Action::Up},
      {GLFW_KEY_E, Action::Down},
      {GLFW_KEY_SPACE, Action::Fire}
    };
    std::unordered_set<Key> currentKeys;
  }

  void key_callback(GLFWwindow* window, Key key, int scancode, int action, int mods);
  void handleInput();
  void on(Action action, const std::function<void()> handler);
}
#endif
