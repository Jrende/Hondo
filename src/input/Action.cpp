#include <set>
#include <iostream>
#include "Action.h"

std::set<Action> repeatables({
  Action::Forward,
  Action::Backward,
  Action::Left,
  Action::Right,
  Action::Up,
  Action::Down,
  Action::Fire,
  Action::Jump,
  Action::Test
});

bool is_repeatable(Action action) {
  return repeatables.count(action) > 0;
}
