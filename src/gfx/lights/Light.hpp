#ifndef HONDO_LIGHT_HPP
#define HONDO_LIGHT_HPP
class Light;
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
class Light {
  private:
  public:
    glm::vec3 pos, color;
    float ambient_intensity, diffuse_intensity;

    Light(glm::vec3 pos, glm::vec3 color);
    void translate(glm::vec3 pos);
};
#endif
