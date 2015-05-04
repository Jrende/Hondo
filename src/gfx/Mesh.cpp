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

Mesh& Mesh::operator=(Mesh&& other) {
    this->index_count = other.index_count;
    this->index_start = other.index_start;
    this->vertex_count = other.vertex_count;
    this->vertex_start = other.vertex_start;
    this->name = std::move(other.name);
    this->material = std::move(other.material);
    this->vertex_array = std::move(other.vertex_array);

    other.index_count = 0;
    other.index_start = 0;
    other.vertex_count = 0;
    other.vertex_start = 0;
    other.name = "";
    other.vertex_array = boost::optional<VertexArray&>();
    return *this;
}

void Mesh::render() {
  if(vertex_array)
    vertex_array->render(*this);
}
