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
  Jump
};
bool isRepeatable(Action action);
#endif
