#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera():
  up({0, 1.0f, 0}),
  pos({0, 0, 0}),
  target({0, 0, 1.0f}),
  view_mat(glm::lookAt(pos, target, up))
  {}

void Camera::translate(glm::vec3 pos) {
  this->pos += pos;
  this->target += pos;
  std::cout << "t (" << target.x << ", " << target.y << ", " << target.z << ")" << std::endl;
}

void Camera::rotate(float angle, glm::vec3 axis) {
  auto rot = glm::rotate(glm::quat{}, angle, axis);
  glm::vec4 nt = glm::mat4_cast(rot) * glm::vec4(target, 1.0f);
  target = glm::vec3{nt.x, nt.y, nt.z};
}

glm::mat4 Camera::get_view_mat() {
  //glm::mat4 view_mat = this->view_mat;
  //view_mat *= glm::mat4_cast(rot);
  //view_mat = glm::translate(view_mat, pos);
  return glm::lookAt(pos, target, up);
}

void Camera::move_forward(float dist) {
  glm::vec3 forward = glm::normalize(target-pos);
  this->translate(dist*forward);
}

void Camera::move_right(float dist) {
  glm::vec3 forward = glm::normalize(target-pos);
  //std::cout << "t (" << forward.x << ", " << forward.y << ", " << forward.z << ")" << std::endl;
  glm::vec3 left = glm::cross(up, forward); 
  this->translate(dist*left);
}
