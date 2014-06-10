#include "RenderObject.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

RenderObject::RenderObject(std::shared_ptr<VertexArray> vArray):
  vArray(vArray),
  modelMatrix(1.0f) {
  
}

void RenderObject::render() {
  vArray->render();
}

void RenderObject::translate(const glm::vec3&& pos) {
  modelMatrix = glm::translate(modelMatrix, pos);
}
