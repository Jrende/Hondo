#ifndef __HONDO_INPUT_H__
#define __HONDO_INPUT_H__
#include <functional>
#include "InputHandler.h"
namespace Input {
  static InputHandler inputHandler;

  static void handleAction(Action action, const std::function<void()>& handler) {
    Input::inputHandler.registerHandler(action, handler);
  }

  static int getMouseX() {
    return 0;
  }

  static int getMouseDX() {
    return 0;
  }

}
#endif
