#ifndef HONDO_INPUT_HPP
#define HONDO_INPUT_HPP
#include <glfw3.h>
#include <functional>
#include <map>
#include <set>
#include <vector>
#include "Actions.hpp"
namespace Input {
  typedef std::function<void()> ActionHandler;
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
  bool is_shift_down();
  bool is_control_down();
  bool is_alt_down();
  bool is_super_down();
  void lock_mouse();
  void set_active_window(GLFWwindow* window);
}
#endif
