#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

Camera::Camera(glm::vec3 pos, glm::vec3 dir):
  up({0, 1.0f, 0}),
  pos(pos),
  dir(dir),
  view_mat(glm::lookAt(pos, pos+dir, up))
  {
  }

void Camera::translate(glm::vec3 pos) {
  this->pos += pos;
  calc_view_mat();
}

void Camera::rotate(float angle, glm::vec3 axis) {
  rot = glm::rotate(rot, angle, axis);
  dir = glm::vec3(glm::vec4(0, 0, 1, 0.0f) * glm::mat4_cast(rot));
  calc_view_mat();
}

void Camera::calc_view_mat() {
  view_mat = glm::lookAt(pos, pos+dir, up);
}

const glm::mat4& Camera::get_view_mat() const {
  return view_mat;
}

void Camera::move_forward(float dist) {
  glm::vec3 temp = dir;
  temp.y = 0;
  temp = glm::normalize(temp);
  this->translate(dist*temp);
  calc_view_mat();
}

void Camera::move_right(float dist) {
  glm::vec3 left = glm::cross(up, -dir);
  this->translate(dist*left);
  calc_view_mat();
}
