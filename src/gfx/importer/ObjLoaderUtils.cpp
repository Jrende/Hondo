#include "ObjLoaderUtils.hpp"
#include <stdio.h>

namespace ObjLoaderUtils {

  std::string popFirstToken(std::vector<std::string>& vec) {
    std::string first = vec[0];
    vec.erase(vec.begin(), vec.begin() + 1);
    return first;
  }

  void calcTangent(Face& face) {
  }

}
