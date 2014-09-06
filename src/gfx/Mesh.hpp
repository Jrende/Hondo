#ifndef HONDO_MESH_HPP
#define HONDO_MESH_HPP
class Mesh;
#include <string>
#include "Material.hpp"
class Mesh {
  private:
  public:
    unsigned int start;
    unsigned int end;
    std::string name;
    Material material;
};
#endif
