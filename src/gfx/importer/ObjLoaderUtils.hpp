#ifndef __HONDO_OBJLOADERUTILS_H__
#define __HONDO_OBJLOADERUTILS_H__

#include <array>
#include <vector>
#include <string>

struct Vertex {
  std::array<float, 3> pos = {{123,123,123}};
  std::array<float, 2> uv = {{123,123}};
  std::array<float, 3> normal = {{123,123,123}};
  std::array<float, 3> tangent = {{123,123,123}};
  std::array<float, 3> bitangent = {{123,123,123}};
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
