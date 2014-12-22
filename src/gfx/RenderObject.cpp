#include "RenderObject.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <GL/glew.h>

RenderObject::RenderObject(Mesh& mesh) :
  mesh(mesh),
  pos(0, 0, 0),
  scale_val(1, 1, 1),
  rot(),
  model_matrix()
{
}

void RenderObject::bind_diffuse() const {
  if(mesh.material.diffuse_map == 0) {
    std::cout << mesh.material.name << " diffuse map not loaded\n";
  }
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, mesh.material.diffuse_map);
}

void RenderObject::bind_normal() const {
  if(mesh.material.normal_map == 0) {
    std::cout << mesh.material.name << " normal map not loaded\n";
  }
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, mesh.material.normal_map);
}

void RenderObject::bind_specular() const {
  if(mesh.material.specular_map == 0) {
    std::cout << mesh.material.name << " specular map not loaded\n";
  }
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
  model_matrix = glm::mat4();
  model_matrix = glm::translate(model_matrix, pos);
  model_matrix = glm::scale(model_matrix, scale_val);
  model_matrix = model_matrix * glm::mat4_cast(rot);
  return model_matrix;
}

void RenderObject::set_position(const glm::vec3& pos) {
  this->pos = pos;
}

void RenderObject::render() {
  mesh.render();
}
