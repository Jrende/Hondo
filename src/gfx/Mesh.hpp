#ifndef HONDO_MESH_HPP
#define HONDO_MESH_HPP
class Mesh;
#include <string>
#include <GL/glew.h>
#include <boost/optional.hpp>
#include "Material.hpp"
#include "VertexArray.hpp"
#include "AABB.hpp"
class Mesh {
  using uint = unsigned int;
  private:
  public:
    uint index_count;
    uint index_start;
    uint vertex_count;
    uint vertex_start;
    //Make into pointers?
    std::string name;
    Material material;
    std::unique_ptr<AABB> aabb = nullptr;
    boost::optional<VertexArray&> vertex_array;

    Mesh();
    Mesh(uint index_start, uint vertex_start, std::string name);
    Mesh(const Mesh& other);

    Mesh operator=(const Mesh& other);

    void render();
};
#endif
