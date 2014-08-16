#ifndef __HONDO_OBJLOADERUTILS_H__
#define __HONDO_OBJLOADERUTILS_H__
#include <array>
#include <vector>
#include <string>
#include <stdio.h>
namespace ObjLoaderUtils {
  template<long long unsigned int n>
    inline std::array<float, n> toFloatArray(const std::vector<std::string>& input) {
      std::array<float, n> ret;
      for(unsigned int i = 0; i < n; i++) {
	ret[i] = strtof(input[i].c_str(), NULL);
      }
      return ret;
    }

  inline std::string popFirstToken(std::vector<std::string>& vec) {
    std::string first = vec[0];
    vec.erase(vec.begin(), vec.begin() + 1);
    return first;
  }

}
#endif
