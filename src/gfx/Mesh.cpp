#include "Mesh.hpp"

void Mesh::render() {
  vertex_array->render(*this);
}
