#include <iostream>
#include "Mesh.hpp"

Mesh::Mesh():
    index_count(0),
    index_start(0),
    vertex_count(0),
    vertex_start(0),
    name("initial"),
    material(),
    aabb(nullptr),
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
    aabb(nullptr),
    vertex_array()
{
}

Mesh Mesh::operator=(const Mesh& other) {
  index_count = other.index_count;
  index_start = other.index_start;
  vertex_count = other.vertex_count;
  vertex_start = other.vertex_start;
  name = other.name;
  material = other.material;
  if(other.aabb != nullptr) {
    aabb = std::make_unique<AABB>(AABB(*other.aabb));
  } else {
    aabb = nullptr;
  }
  vertex_array = other.vertex_array;

  return *this;
}

Mesh::Mesh(const Mesh& other):
  index_count(other.index_count),
  index_start(other.index_start),
  vertex_count(other.vertex_count),
  vertex_start(other.vertex_start),
  name(other.name),
  material(other.material),
  aabb(nullptr),
  vertex_array(other.vertex_array)
{
  if(other.aabb != nullptr) {
    aabb = std::make_unique<AABB>(AABB(*other.aabb));
  }
}

void Mesh::render() {
  if(vertex_array)
    vertex_array->render(*this);
}
