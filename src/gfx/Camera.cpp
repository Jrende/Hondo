#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

Camera::Camera():
  up({0, 1.0f, 0}),
  pos({0, 0, 0}),
  forward({0, 0, 1.0f}),
  view_mat(glm::lookAt(pos, forward, up))
  { }

void Camera::translate(glm::vec3 pos) {
  view_mat = glm::translate(view_mat, pos);
}
