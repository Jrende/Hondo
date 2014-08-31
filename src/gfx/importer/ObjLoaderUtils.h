#ifndef __HONDO_OBJLOADERUTILS_H__
#define __HONDO_OBJLOADERUTILS_H__
#include "ObjLoader.hpp"
#include <array>
#include <vector>
#include <string>
namespace ObjLoaderUtils {
  template<long long unsigned int n>
  inline std::array<float, n> toFloatArray(const std::vector<std::string>& input);;
  inline std::string popFirstToken(std::vector<std::string>& vec);
  void calcTangent(Face& face);
}
#endif
