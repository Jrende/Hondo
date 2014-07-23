#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "VertexArray.h"
#include <GL/glew.h>
#include <glfw3.h>

VertexArray::VertexArray(const std::vector<float>& vertex_data, uint vertex_count, std::vector<uint> attribute_sizes):
  vertex_count(vertex_count),
  attribute_sizes(attribute_sizes),
  vertex_data(vertex_data)
{
  init();
  flip();
}


VertexArray::VertexArray(uint vertex_count, std::vector<uint> attribute_sizes):
  vertex_count(vertex_count),
  attribute_sizes(attribute_sizes)
{
  init();
}

VertexArray::VertexArray(const VertexArray& other):
  vertex_count(other.vertex_count),
  attribute_sizes(other.attribute_sizes),
  vertex_data(other.vertex_data),
  attr_size_sum(other.attr_size_sum),
  vao_id(other.vao_id),
  vbo_id(other.vbo_id),
  index_buf_id(other.index_buf_id)
{
  std::cout << "Invoked copy constructor of VertexArray" << std::endl;
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &vao_id);
  glDeleteBuffers(1, &vbo_id);
  glDeleteBuffers(1, &index_buf_id);
}

void VertexArray::init() {
  attr_size_sum = 0;
  for(uint& i: attribute_sizes)
    attr_size_sum += i;

  vertex_data.reserve(vertex_count * attr_size_sum);

  glGenVertexArrays(1, &vao_id);
  glGenBuffers(1, &vbo_id);
  glGenBuffers(1, &index_buf_id);
}

void VertexArray::flip(void) {
  int data_size = attr_size_sum * vertex_count * sizeof(float);
  std::cout << "flip" << std::endl;

  glBindVertexArray(vao_id);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glBufferData(GL_ARRAY_BUFFER, data_size, vertex_data.data(), GL_STATIC_DRAW);

  int pointer = 0;
  for(uint i = 0; i < attribute_sizes.size(); i++) {
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, attribute_sizes[i], GL_FLOAT, GL_TRUE, attr_size_sum * sizeof(float), (void*)(pointer * sizeof(float)));
    pointer += attribute_sizes[i];
    glDisableVertexAttribArray(i);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  auto index_buf_data = std::vector<uint>();
  for(int i = 0; i < vertex_count; i++) {
    index_buf_data.push_back(i);
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buf_data.size() * sizeof(uint), index_buf_data.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexArray::render(void) {
  glBindVertexArray(vao_id);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf_id);
  glDrawArrays(GL_TRIANGLES, 0, vertex_count);
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
