#include "Input.h"
#include <iostream>

namespace Input {
  namespace {
    void handle_key(Key key) {
      if(mappings.count(key) > 0) {
	//Get action related to key
	Action action = mappings[key];
	//And iterate through the actions listeners
	for(auto handler: handlers[action]) {
	  handler();
	}
      }
    }
  }

  void key_callback(GLFWwindow* window, Key key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS) {
      if (key == GLFW_KEY_ESCAPE) {
	glfwSetWindowShouldClose(window, GL_TRUE);
      }
      handle_key(key);
      //TODO:Only insert if repeat
      if(mappings.count(key) > 0 && is_repeatable(mappings[key])) {
	currentKeys.insert(key);
      }
    } else if(action == GLFW_RELEASE) {
      currentKeys.erase(key);
    }
  }

  void handle_input() {
    for(Key key: currentKeys) {
      handle_key(key);
    }
  }

  void on(Action action, const std::function<void()> handler) {
    handlers[action].push_back(handler); 
  }
  
  void cursor_pos_callback(GLFWwindow* window, double x, double y) {
    Input::deltaX = mouseX - x;
    Input::deltaY = mouseY - y;
    Input::mouseX = x;
    Input::mouseY = y;
  }

  double get_mouse_x() {
    return Input::mouseX;
  }
  double get_mouse_y() {
    return Input::mouseY;
  }
  double get_mouse_dx() {
    return Input::deltaX;
  }
  double get_mouse_dy() {
    return Input::deltaY;
  }

  void reset_delta() {
    Input::deltaX = 0;
    Input::deltaY = 0;
  }

  bool is_key_down(Key key) {
      return currentKeys.count(key) != 0;
  }

  void lock_mouse() {
    if(mouseLocked) {
      glfwSetInputMode(Input::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } else {
      glfwSetInputMode(Input::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    mouseLocked = !mouseLocked;
  }

  void set_active_window(GLFWwindow* window) {
    Input::window = window;
  }
}
