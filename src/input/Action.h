#ifndef __HONDO_ACTION_H__
#define __HONDO_ACTION_H__
//Add repeat
enum class Action {
  Forward,
  Backward,
  Left,
  Right,
  Fire,
  Jump
};
bool isRepeatable(Action action);
#endif
