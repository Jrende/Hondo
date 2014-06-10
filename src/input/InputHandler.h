#ifndef __HONDO_INPUTHANDLER_H__
#define __HONDO_INPUTHANDLER_H__
class InputHandler;
#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Action.h"
typedef int Key;
typedef std::function<void()> ActionHandler;
class InputHandler {
  private:
    std::unordered_map< Action, std::vector<ActionHandler> > handlers;
    std::unordered_map<Key, Action> mappings;
    std::unordered_set<Key> currentKeys;
    void handleKey(Key key);
  public:
    InputHandler();
    void registerHandler(Action action, ActionHandler fun);
    void handleInput();
    void key_callback(GLFWwindow* window, Key key, int scancode, int action, int mods);
};
#endif
