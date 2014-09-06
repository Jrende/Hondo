#ifndef HONDO_ACTIONS_HPP
#define HONDO_ACTIONS_HPP
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
