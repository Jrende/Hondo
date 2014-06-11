#include <unordered_map>
#include <iostream>
#include "Action.h"

const std::unordered_map<Action, bool> repeatables({
  {Action::Forward, true}, 
  {Action::Backward, true}, 
  {Action::Left, true}, 
  {Action::Right, true}, 
  {Action::Up, true}, 
  {Action::Down, true}, 
  {Action::Fire, false}, 
  {Action::Jump, false}
});

bool isRepeatable(Action action) {
  return repeatables.count(action) > 0;
}
