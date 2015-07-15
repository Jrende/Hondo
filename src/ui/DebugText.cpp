#include "DebugText.hpp"

namespace DebugText {
  namespace detail {
    std::unordered_map<std::string, std::string> lines;
    NVGcontext* vg;
  }

  void set_context(NVGcontext* context) {
    detail::vg = context;
  }

  template<>
  void set_value(std::string attr, char const* value) {
    detail::lines[attr] = value;
  }

  void draw() {
    int line_num = 0;
    for(const auto& line: detail::lines) {
      nvgFontFace(detail::vg, "sans");
      std::string str = line.first + ": " + line.second;
      nvgText(detail::vg, 10, line_num * 20 + 15, str.c_str(), nullptr);
      line_num++;
    }
  }

}
