#include "RenderObject.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <GL/glew.h>

RenderObject::RenderObject(const VertexArray& vertex_array, const Mesh& mesh) :
  mesh(mesh),
  vertex_array(vertex_array),
  pos(0, 0, 0),
  scale_val(1, 1, 1),
  model_matrix(),
  rot()
{
}

RenderObject::RenderObject(const RenderObject& other):
  mesh(other.mesh),
  vertex_array(other.vertex_array),
  pos(other.pos),
  scale_val(other.scale_val),
  model_matrix(other.model_matrix),
  rot(other.rot)
{
  std::cout << "Invoked RenderObject copy constructor" << std::endl;
}

void RenderObject::bind_diffuse() const {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, mesh.material.diffuse_map);
}

void RenderObject::bind_normal() const {
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, mesh.material.normal_map);
}

void RenderObject::bind_specular() const {
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, mesh.material.specular_map);
}

void RenderObject::translate(const glm::vec3& pos) {
  this->pos += pos;
}

void RenderObject::scale(const glm::vec3& scale) {
  this->scale_val *= scale;
}

void RenderObject::rotate(float angle, const glm::vec3& axis) {
  rot = glm::rotate(rot, angle, axis);
}

const glm::mat4& RenderObject::get_model_matrix() {
  model_matrix = glm::mat4(1.0f);
  model_matrix = glm::translate(model_matrix, pos);
  model_matrix = glm::scale(model_matrix, scale_val);
  model_matrix = model_matrix * glm::mat4_cast(rot);
  return model_matrix;
}

void RenderObject::set_position(const glm::vec3& pos) {
  this->pos = pos;
}

void RenderObject::render() const {
  vertex_array.render(mesh);
}
