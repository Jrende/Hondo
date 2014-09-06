#ifndef __HONDO_POINTLIGHT_H__
#define __HONDO_POINTLIGHT_H__
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
