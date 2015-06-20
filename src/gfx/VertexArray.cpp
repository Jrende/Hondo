#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexArray.hpp"
VertexArray::VertexArray(
    const std::vector<float>& vertex_data,
    const std::vector<unsigned int>& index_data,
    std::vector<unsigned int> attribute_sizes
  ):
  attribute_sizes(attribute_sizes),
  vertex_data(vertex_data),
  index_data(index_data)
{
  init();
  create_buffers();
}

VertexArray::VertexArray(const VertexArray& other):
  attribute_sizes(other.attribute_sizes),
  vertex_data(other.vertex_data),
  index_data(other.index_data),
  vao_id(other.vao_id),
  vbo_id(other.vbo_id),
  index_buf_id(other.index_buf_id)
{
}

VertexArray& VertexArray::operator=(VertexArray&& other) {
  swap(*this, other);
  return *this;
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &vao_id);
  glDeleteBuffers(1, &vbo_id);
  glDeleteBuffers(1, &index_buf_id);
}

void VertexArray::init() {
  glGenVertexArrays(1, &vao_id);
  glGenBuffers(1, &vbo_id);
  glGenBuffers(1, &index_buf_id);
}


void VertexArray::create_buffers() {
  unsigned int attr_size_sum = 0;
  for(unsigned int& i: attribute_sizes)
    attr_size_sum += i;

  glBindVertexArray(vao_id);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_data.size(), vertex_data.data(), GL_STATIC_DRAW);

  int pointer = 0;
  for(unsigned int i = 0; i < attribute_sizes.size(); i++) {
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, attribute_sizes[i], GL_FLOAT, GL_TRUE, attr_size_sum * sizeof(float), (void*)(pointer * sizeof(float)));
    pointer += attribute_sizes[i];
    glDisableVertexAttribArray(i);
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data.size() * sizeof(unsigned int), index_data.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

void VertexArray::bind() const {
  glBindVertexArray(vao_id);
  for(unsigned int i = 0; i < attribute_sizes.size(); i++)
    glEnableVertexAttribArray(i);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf_id);
}

void VertexArray::render(const Mesh& mesh) const {
  glDrawElementsBaseVertex(
      GL_TRIANGLES,
      mesh.index_count,
      GL_UNSIGNED_INT,
      (void*) (mesh.index_start * sizeof(unsigned int)),
      mesh.vertex_start
  );
}

void VertexArray::render_elements(GLuint mode, unsigned int size) {
  glDrawElements(mode, size, GL_UNSIGNED_INT, (void*) 0);
}

void VertexArray::unbind() const {
  for(unsigned int i = 0; i < attribute_sizes.size(); i++)
    glDisableVertexAttribArray(i);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

bool VertexArray::operator<(const VertexArray& other) const {
  return this->vao_id < other.vao_id;
}

bool VertexArray::operator==(const VertexArray& other) const {
  return this->vao_id == other.vao_id;
}

bool VertexArray::operator!=(const VertexArray& other) const {
  return this->vao_id != other.vao_id;
}

void VertexArray::swap(VertexArray& l, VertexArray& r) {
  std::swap(l.vertex_data, r.vertex_data);
  std::swap(l.index_data, r.index_data);
  std::swap(l.attribute_sizes, r.attribute_sizes);
  std::swap(l.vao_id, r.vao_id);
  std::swap(l.vbo_id, r.vbo_id);
  std::swap(l.index_buf_id, r.index_buf_id);
}
