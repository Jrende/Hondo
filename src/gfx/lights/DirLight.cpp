#include "DirLight.hpp"

DirLight::DirLight(glm::vec3 dir, glm::vec3 color):
  Light(glm::vec3(-1, -1, -1), dir, color)
{
}
