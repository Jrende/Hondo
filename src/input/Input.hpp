#ifndef __HONDO_INPUT_H__
#define __HONDO_INPUT_H__
#include <glfw3.h>
#include <functional>
#include <map>
#include <set>
#include <vector>
#include "Actions.hpp"
namespace Input {
  typedef std::function<void()> ActionHandler;
  namespace {
    std::map<int, ActionHandler> handlers;
    std::set<int> currentKeys;
    double mouseX;
    double mouseY;
    double deltaX;
    double deltaY;
    bool mouseLocked;
    GLFWwindow* window;
  }
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  void cursor_pos_callback(GLFWwindow* window, double x, double y);
  void reset_delta();
  void handle_input();
  void on(int key, const std::function<void()>& handler);
  void on(int key, const std::function<void()>& handler, bool repeat);
  double get_mouse_x();
  double get_mouse_y();
  double get_mouse_dx();
  double get_mouse_dy();
  bool is_key_down(int key);
  void lock_mouse();
  void set_active_window(GLFWwindow* window);
}
#endif
