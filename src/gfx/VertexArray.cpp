#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(): vertex_data() {
  glGenVertexArrays(1, &vao_id);
  glGenBuffers(1, &vbo_id);
  glGenBuffers(1, &index_buf_id);
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &vao_id);
  glDeleteBuffers(1, &vbo_id);
  glDeleteBuffers(1, &index_buf_id);
}

int VertexArray::size() {
  return this->vertex_data.size();
}

void VertexArray::add_vertex(float x, float y, float z) {
  vertex_data.push_back(x);
  vertex_data.push_back(y);
  vertex_data.push_back(z);
}

void VertexArray::print() {
  for(float f: vertex_data) {
    std::cout << f << ", ";
  }
  std::cout << std::endl;
}

void VertexArray::flip() {
  /*
  int size = pos_len * vertex_data.size() * sizeof(float);

  glBindVertexArrays(vao_id);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glBufferData(GL_ARRAY_BUFFER, size, vertex_data.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, pos_len, GL_FLOAT, GL_TRUE, 0, NULL)
  glDisableVertexAttribArray(0);

  glBindBuffer(0);
  glBindVertexArray(0);
  
  int[vertex_data.size] index_buf_data;
  for(int i = 0; i < vertex_data.size(); i++) {
    index_buf_data[i] = i;
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, &index_buf_data, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  */
}

void VertexArray::render() {

}
