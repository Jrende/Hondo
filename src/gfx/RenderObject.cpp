#include "RenderObject.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <GL/glew.h>

//Should remove this
RenderObject::RenderObject():
  transform(),
  mesh(),
  aabb()
{
}

RenderObject::RenderObject(Mesh& mesh) :
  transform(),
  mesh(mesh),
  aabb(*mesh.aabb)
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

void RenderObject::bind_mask() const {
  if(mesh.material.mask == 0) {
    std::cout << mesh.material.name << " mask not loaded\n";
  }
  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, mesh.material.mask);
}

void RenderObject::render() {
  mesh.render();
}

void RenderObject::update_aabb() {
  aabb.transform(transform.model_matrix);
}
