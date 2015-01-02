#include "SpotLight.hpp"

SpotLight::SpotLight(glm::vec3 pos, glm::vec3 dir, glm::vec3 color):
  Light(pos, dir, color),
  concentration(10),
  constant(0.5f),
  linear(0.1f),
  exponential(0.1f)
{
}
