#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
Camera::Camera():
  up({0, 1.0f, 0}),
  pos({0, 0, 0}),
  forward({0, 0, 1.0f}),
  viewMat(glm::lookAt(pos, forward, up))
  { }

void Camera::translate(glm::vec3 pos) {
  viewMat = glm::translate(viewMat, pos);
}
