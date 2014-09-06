#include "PointLight.hpp"

PointLight::PointLight(glm::vec3 pos, glm::vec3 color):
  Light(pos, color),
  constant(0.1f),
  linear(0.1f),
  exponential(0.1f)
{
}
