#include "RenderObject.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

RenderObject::RenderObject(std::shared_ptr<VertexArray> vertex_array, Mesh mesh):
  mesh(mesh),
  vertex_array(vertex_array)
{
}

void RenderObject::render() const {
  vertex_array->render(mesh);
}

void RenderObject::translate(const glm::vec3& pos) {
  model_matrix = glm::translate(model_matrix, pos);
}
