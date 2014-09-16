#ifndef HONDO_OBJLOADERUTILS_HPP
#define HONDO_OBJLOADERUTILS_HPP

#include <array>
#include <vector>
#include <string>

struct Vertex {
  std::array<float, 3> pos;
  std::array<float, 2> uv;
  std::array<float, 3> normal;
  std::array<float, 3> tangent;
  std::array<float, 3> bitangent;
  bool isIndexed = false;
};

struct Face {
  std::vector<Vertex> verts;
};

namespace ObjLoaderUtils {
  template<long long unsigned int n>
  std::array<float, n> toFloatArray(const std::vector<std::string>& input) {
    std::array<float, n> ret;
    for(unsigned int i = 0; i < n; i++) {
      ret[i] = strtof(input[i].c_str(), NULL);
    }
    return ret;
  }

  std::string popFirstToken(std::vector<std::string>& vec);
  void calcTangent(Face& face);
}
#endif
