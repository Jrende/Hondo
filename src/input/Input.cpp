#include "Input.h"
#include <iostream>

namespace Input {
  namespace {
    void handleKey(Key key) {
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
      handleKey(key);
      //TODO:Only insert if repeat
      if(mappings.count(key) > 0 && isRepeatable(mappings[key])) {
	currentKeys.insert(key);
      }
    } else if(action == GLFW_RELEASE) {
      currentKeys.erase(key);
    }
  }

  void handleInput() {
    for(Key key: currentKeys) {
      handleKey(key);
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

  double getMouseX() {
    return Input::mouseX;
  }
  double getMouseY() {
    return Input::mouseY;
  }
  double getMouseDX() {
    return Input::deltaX;
  }
  double getMouseDY() {
    return Input::deltaY;
  }

  void resetDelta() {
    Input::deltaX = 0;
    Input::deltaY = 0;
  }
}
