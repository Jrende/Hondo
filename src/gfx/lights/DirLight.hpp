#pragma once
class DirLight;
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Light.hpp"
class DirLight: public Light {
  private:
  public:
    DirLight(glm::vec3 dir, glm::vec3 color);
};
