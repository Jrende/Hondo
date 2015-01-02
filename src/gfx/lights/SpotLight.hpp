#ifndef HONDO_SPOTLIGHT_HPP
#define HONDO_SPOTLIGHT_HPP
class SpotLight;
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Light.hpp"
class SpotLight: public Light {
  private:
  public:
    float radius, concentration, constant, linear, exponential;
    SpotLight(glm::vec3 pos, glm::vec3 dir, glm::vec3 color);
};
#endif
