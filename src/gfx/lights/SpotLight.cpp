#include "SpotLight.hpp"

SpotLight::SpotLight(glm::vec3 pos, glm::vec3 dir, glm::vec3 color):
  Light(pos, color),
  dir(dir),
  concentration(10),
  constant(0.1f),
  linear(0.1f),
  exponential(0.1f)
{
}
