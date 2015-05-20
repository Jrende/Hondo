#define GLM_FORCE_RADIANS
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
}

void Transform::set_position(const glm::vec3& pos) {
  this->pos = pos;
}

void Transform::scale(const glm::vec3& scale) {
  this->scale_val *= scale;
}

void Transform::rotate(float angle, const glm::vec3& axis) {
  rot = glm::rotate(rot, angle, axis);
}

const glm::mat4& Transform::get_model_matrix() {
  model_matrix = glm::mat4();
  model_matrix = glm::translate(model_matrix, pos);
  model_matrix = glm::scale(model_matrix, scale_val);
  model_matrix = model_matrix * glm::mat4_cast(rot);
  return model_matrix;
}
