#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

Camera::Camera():
  up({0, 1.0f, 0}),
  pos({0, 0, 0}),
  dir({0, 0, 1.0f}),
  view_mat(glm::lookAt(pos, dir+pos, up))
  {}

void Camera::translate(glm::vec3 pos) {
  this->pos += pos;
}

void Camera::rotate(float angle, glm::vec3 axis) {
  rot = glm::rotate(rot, angle, axis);
  dir = glm::vec3(glm::vec4(0, 0, 1, 0.0f) * glm::mat4_cast(rot));
}

glm::mat4 Camera::get_view_mat() {
  view_mat = glm::mat4{};
  view_mat = glm::mat4_cast(rot) * view_mat;
  view_mat = glm::translate(view_mat, pos);
  return view_mat;
}

void Camera::move_forward(float dist) {
  glm::vec3 temp = dir;
  temp.y = 0;
  temp = glm::normalize(temp);
  this->translate(dist*temp);
}

void Camera::move_right(float dist) {
  glm::vec3 left = glm::cross(up, dir); 
  this->translate(dist*left);
}
