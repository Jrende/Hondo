#include "Light.hpp"

Light::Light(glm::vec3 pos, glm::vec3 color): 
  pos(pos),
  color(color),
  ambient_intensity(0.1125f),
  diffuse_intensity(0.25f)
{
}

void Light::translate(glm::vec3 pos) {
  this->pos += pos;
}
