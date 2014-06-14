#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "VertexArray.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

VertexArray::VertexArray(): vertex_data() {
  glGenVertexArrays(1, &vao_id);
  glGenBuffers(1, &vbo_id);
  glGenBuffers(1, &index_buf_id);
}

VertexArray::VertexArray(const VertexArray& other):
  vao_id(other.vao_id),
  vbo_id(other.vbo_id),
  index_buf_id(other.index_buf_id),
  //vertex_data(other.vertex_data),
  vertex_len(other.vertex_len) {
  std::cout << "Invoked copy constructor of VertexArray" << std::endl;
}

VertexArray::VertexArray(std::vector<std::vector<float>> vertices): VertexArray() {
  this->add_vertices(vertices); 
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &vao_id);
  glDeleteBuffers(1, &vbo_id);
  glDeleteBuffers(1, &index_buf_id);
}

int VertexArray::size(void) {
  return this->vertex_data.size();
}

void VertexArray::add_vertex(float x, float y, float z) {
  vertex_data.push_back(x);
  vertex_data.push_back(y);
  vertex_data.push_back(z);
  vertex_len++;
}

void VertexArray::add_vertices(const std::vector<std::vector<float> > &vertices) {
  for(int i = 0; i < vertices.size(); i += 1) {
    vertex_data.push_back(vertices[i][0]);
    vertex_data.push_back(vertices[i][1]);
    vertex_data.push_back(vertices[i][2]);
  }
  vertex_len += vertices.size();
}

void VertexArray::flip(void) {
  int size = pos_len * vertex_data.size() * sizeof(float);

  glBindVertexArray(vao_id);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glBufferData(GL_ARRAY_BUFFER, size, vertex_data.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, pos_len, GL_FLOAT, GL_TRUE, 0, NULL);
  glDisableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  int index_buf_data[vertex_data.size()];
  for(int i = 0; i < vertex_data.size(); i++) {
    index_buf_data[i] = i;
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertex_data.size() * sizeof(int), &index_buf_data, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexArray::render(void) {
  glBindVertexArray(vao_id);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf_id);
  glDrawElements(GL_TRIANGLES, vertex_len, GL_UNSIGNED_INT, NULL);
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
