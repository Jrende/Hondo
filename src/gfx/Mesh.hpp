#ifndef HONDO_MESH_HPP
#define HONDO_MESH_HPP
class Mesh;
#include <string>
#include "Material.hpp"
#include "VertexArray.hpp"
class Mesh {
  private:
  public:
    unsigned int count;
    unsigned int start;
    unsigned int base_vertex;
    std::string name;
    Material material;
    std::shared_ptr<VertexArray> vertex_array;
};
#endif
