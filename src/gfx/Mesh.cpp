#include <iostream>
#include "Mesh.hpp"

Mesh::Mesh():
    index_count(0),
    index_start(0),
    vertex_count(0),
    vertex_start(0),
    name("initial"),
    material(),
    vertex_array()
{
}

Mesh::Mesh(uint index_start, uint vertex_start, std::string name):
    index_count(0),
    index_start(index_start),
    vertex_count(0),
    vertex_start(vertex_start),
    name(name),
    material(),
    vertex_array()
{
}

void Mesh::render() {
  if(vertex_array)
    vertex_array->render(*this);
}
