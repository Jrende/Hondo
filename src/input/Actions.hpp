#ifndef __HONDO_ACTIONS_H__
#define __HONDO_ACTIONS_H__
//Add repeat
namespace Actions {
  extern int Forward;
  extern int Backward;
  extern int Left;
  extern int Right;
  extern int Up;
  extern int Down;
  bool is_repeatable(int action);
  void set_repeatable(int action);
}
#endif
