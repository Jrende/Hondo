#include "InputHandler.h"
#include <sstream>
#include <iostream>

InputHandler::InputHandler() {
  //TODO: Parse a file for inputs
  mappings[GLFW_KEY_W] = Action::Forward;
  mappings[GLFW_KEY_S] = Action::Backward;
  mappings[GLFW_KEY_A] = Action::Left;
  mappings[GLFW_KEY_D] = Action::Right;
  mappings[GLFW_KEY_Q] = Action::Up;
  mappings[GLFW_KEY_E] = Action::Down;
  mappings[GLFW_KEY_SPACE] = Action::Fire;
}

void InputHandler::key_callback(GLFWwindow* window, Key key, int scancode, int action, int mods) {
  if(action == GLFW_PRESS) {
    handleKey(key);
    //TODO:Only insert if repeat
    if(mappings.count(key) > 0 && isRepeatable(mappings[key])) {
      currentKeys.insert(key);
    }
  } else if(action == GLFW_RELEASE) {
    currentKeys.erase(key);
  }
}

void InputHandler::handleKey(Key key) {
  if(mappings.count(key) > 0) {
    Action action = mappings[key];
    for(auto handler: handlers[action]) {
      handler();
    }
  }
}

void InputHandler::handleInput() {
  for(Key key: currentKeys) {
    handleKey(key);
  }
}

void InputHandler::registerHandler(Action action, const ActionHandler& fun) {
  handlers[action].push_back(fun);
}
