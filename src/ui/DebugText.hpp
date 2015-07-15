class DebugTextUI;
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <nanovg.h>
#include <iostream>

#pragma once
namespace DebugText {
  namespace detail {
    extern std::unordered_map<std::string, std::string> lines;
    extern NVGcontext* vg;
  }

  void set_context(NVGcontext* context);

  template<typename T>
  void set_value(std::string attr, T value) {
    detail::lines[attr] = std::to_string(value);
  }

  template<>
  void set_value(std::string attr, char const* value);

  void draw();
}
