#include "Triangle.h"

Triangle::Triangle(): vArray() {
  vArray.add_vertex(0.0f, 0.0f, 0.0f);
  vArray.add_vertex(1.0f, 0.0f, 0.0f);
  vArray.add_vertex(0.0f, 1.0f, 0.0f);
}

void Triangle::render() {
  vArray.render();
}
