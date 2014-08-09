#include "RenderObject.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <GL/glew.h>

RenderObject::RenderObject(std::shared_ptr<VertexArray> vertex_array, Mesh mesh):
  vertex_array(vertex_array),
  mesh(mesh)
{
}

void RenderObject::render() const {
  vertex_array->render(mesh);
}

RenderObject::RenderObject(const RenderObject& other):
    vertex_array(other.vertex_array),
    color(other.color),
    model_matrix(other.model_matrix),
    mesh(other.mesh)
{
  std::cout << "RenderObject copy constructor called" << std::endl;

}

void RenderObject::bind_material(SimpleShader& simple_shader) const {
  simple_shader.set_diffuse_sampler(0);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, mesh.material.diffuse_map);
}

void RenderObject::translate(const glm::vec3& pos) {
  model_matrix = glm::translate(model_matrix, pos);
}

void RenderObject::set_position(const glm::vec3& pos) {
  model_matrix[3][0] = pos.x;
  model_matrix[3][1] = pos.y;
  model_matrix[3][2] = pos.z;
}
