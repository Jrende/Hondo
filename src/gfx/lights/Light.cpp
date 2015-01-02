#include "Light.hpp"
Light::Light(glm::vec3 pos, glm::vec3 dir, glm::vec3 color):
  camera(pos, dir),
  color(color),
  ambient_intensity(0.1125f),
  diffuse_intensity(0.25f)
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
