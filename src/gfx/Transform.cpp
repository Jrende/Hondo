#include "Transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
Transform::Transform():
  pos(0, 0, 0),
  scale_val(1, 1, 1),
  rot(),
  model_matrix()
{
}

void Transform::translate(const glm::vec3& pos) {
  this->pos += pos;
  model_matrix = glm::translate(model_matrix, pos);
}

void Transform::set_position(const glm::vec3& pos) {
  this->pos = pos;
  model_matrix[3][0] = pos.x;
  model_matrix[3][1] = pos.y;
  model_matrix[3][2] = pos.z;
}

void Transform::scale(const glm::vec3& scale) {
  this->scale_val *= scale;
  model_matrix = glm::scale(model_matrix, scale);
}

void Transform::rotate(const glm::quat& rot) {
  this->rot *= rot;
  model_matrix = model_matrix * glm::mat4_cast(rot);
}

void Transform::rotate(float angle, const glm::vec3& axis) {
 this->rot = glm::rotate(rot, angle, axis);
}

const glm::mat4& Transform::get_model_matrix() const {
  return model_matrix;
}

const glm::vec3& Transform::get_pos() {
  return pos;
}

const glm::quat& Transform::get_rot() {
  return rot;
}

const glm::vec3& Transform::get_scale() {
  return scale_val;
}
