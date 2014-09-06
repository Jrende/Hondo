#ifndef HONDO_POINTLIGHT_HPP
#define HONDO_POINTLIGHT_HPP
class PointLight;
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Light.hpp"
class PointLight: public Light {
  private:
  public:
    float constant, linear, exponential;
    PointLight(glm::vec3 pos, glm::vec3 color);
};
#endif
