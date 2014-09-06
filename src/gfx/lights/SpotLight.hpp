#ifndef __HONDO_SPOTLIGHT_H__
#define __HONDO_SPOTLIGHT_H__
class SpotLight;
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Light.hpp"
class SpotLight: public Light {
  private:
  public:
    glm::vec3 dir;
    float radius, concentration, constant, linear, exponential;
    SpotLight(glm::vec3 pos, glm::vec3 dir, glm::vec3 color);
};
#endif
