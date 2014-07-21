#include "Triangle.h"

Triangle::Triangle(): vertex_array() {
  vertex_array.add_vertex(0.0f, 0.0f, 0.0f);
  vertex_array.add_vertex(1.0f, 0.0f, 0.0f);
  vertex_array.add_vertex(0.0f, 1.0f, 0.0f);
}

void Triangle::render() {
  vertex_array.render();
}
