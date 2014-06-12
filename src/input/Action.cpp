#include <unordered_set>
#include <iostream>
#include "Action.h"

const std::unordered_set<Action> repeatables({
  Action::Forward, 
  Action::Backward, 
  Action::Left, 
  Action::Right, 
  Action::Up, 
  Action::Down, 
  Action::Fire, 
  Action::Jump
});

bool isRepeatable(Action action) {
  return repeatables.count(action) > 0;
}
