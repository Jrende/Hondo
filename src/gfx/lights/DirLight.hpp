#pragma once
class DirLight;
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Light.hpp"
class DirLight: public Light {
  private:
    glm::mat4 ortho;
  public:
    DirLight(glm::vec3 dir, glm::vec3 color);
    virtual const glm::mat4& get_projection() const override;
};
