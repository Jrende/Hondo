#include "DirLight.hpp"
#include <glm/gtc/matrix_transform.hpp>

DirLight::DirLight(glm::vec3 dir, glm::vec3 color):
  Light(glm::vec3(0, 0, 0), dir, color),
  ortho(glm::ortho<float>(-10,10,-10,10,-0,10))
{
}

const glm::mat4& DirLight::get_projection() const {
  return ortho;
}
