#ifndef __HONDO_INPUT_H__
#define __HONDO_INPUT_H__
#include <glfw3.h>
#include <functional>
#include <map>
#include <set>
#include <vector>
#include "Action.h"
namespace Input {
  typedef int Key;
  typedef std::function<void()> ActionHandler;
  namespace {
    std::map< Action, std::vector<ActionHandler> > handlers;
    std::map<Key, Action>&& mappings = {
      {GLFW_KEY_W, Action::Forward},
      {GLFW_KEY_S, Action::Backward},
      {GLFW_KEY_A, Action::Left},
      {GLFW_KEY_D, Action::Right},
      {GLFW_KEY_SPACE, Action::Up},
      {GLFW_KEY_LEFT_SHIFT, Action::Down},
      {GLFW_KEY_SPACE, Action::Fire},
      {GLFW_KEY_G, Action::LockMouse},
      {GLFW_KEY_T, Action::Test},
    };
    std::set<Key> currentKeys;
    double mouseX;
    double mouseY;
    double deltaX;
    double deltaY;
    bool mouseLocked;
    GLFWwindow* window;
  }
  void key_callback(GLFWwindow* window, Key key, int scancode, int action, int mods);
  void cursor_pos_callback(GLFWwindow* window, double x, double y);
  void reset_delta();
  void handle_input();
  void on(Action action, const std::function<void()> handler);
  double get_mouse_x();
  double get_mouse_y();
  double get_mouse_dx();
  double get_mouse_dy();
  bool is_key_down(Key key);
  void lock_mouse();
  void set_active_window(GLFWwindow* window);
}
#endif
