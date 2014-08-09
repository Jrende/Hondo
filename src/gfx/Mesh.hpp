#ifndef __HONDO_MESH_H__
#define __HONDO_MESH_H__
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
