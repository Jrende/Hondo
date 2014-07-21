#ifndef __HONDO_ACTION_H__
#define __HONDO_ACTION_H__
//Add repeat
enum class Action {
  Forward,
  Backward,
  Left,
  Right,
  Up,
  Down,
  Fire,
  Jump,
  LockMouse,
  Test,
};

bool is_repeatable(Action action);
#endif
