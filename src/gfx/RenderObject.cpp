#include "RenderObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

RenderObject::RenderObject(std::shared_ptr<VertexArray> vArray):
  vArray(vArray),
  model_matrix(1.0f) {
  }
RenderObject::RenderObject(const RenderObject& other):
  vArray(other.vArray),
  model_matrix(other.model_matrix),
  color(other.color) {
  }

void RenderObject::render() {
  vArray->render();
}

void RenderObject::translate(const glm::vec3& pos) {
  model_matrix = glm::translate(model_matrix, pos);
}
