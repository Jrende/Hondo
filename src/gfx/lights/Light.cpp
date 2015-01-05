#include "Light.hpp"
#include <glm/gtc/matrix_transform.hpp>
Light::Light(glm::vec3 pos, glm::vec3 dir, glm::vec3 color):
  camera(pos, dir),
  shadow_map(DepthBuffer()),
  color(color),
  ambient_intensity(0.1125f),
  diffuse_intensity(0.25f),
  perspective_mat(glm::perspective<float>(45.0f, (float) 1024.0/768, 1.0f, 100.0f))
{
}

void Light::translate(glm::vec3 pos) {
  camera.translate(pos);
  m_has_moved = true;
}

const glm::vec3& Light::get_pos() const {
  return camera.pos;
}

const glm::vec3& Light::get_dir() const {
  return camera.dir;
}

bool Light::has_moved(){
  return m_has_moved;
}

void Light::set_casts_shadow(bool casts_shadow) {
  m_casts_shadow = casts_shadow;
}

const glm::mat4& Light::get_view_mat() const {
  return camera.get_view_mat();
}

bool Light::casts_shadow(){
  return m_casts_shadow;
}

void Light::set_has_moved(bool has_moved) {
  m_has_moved = has_moved;
}

const glm::mat4& Light::get_projection() const {
  return perspective_mat;
}
