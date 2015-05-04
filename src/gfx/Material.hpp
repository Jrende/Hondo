#ifndef HONDO_MATERIAL_HPP
#define HONDO_MATERIAL_HPP
class Material;
#include <string>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <GL/glew.h>
class Material {
  private:
  public:
    std::string name;

    GLuint diffuse_map = 0;
    GLuint specular_map = 0;
    GLuint normal_map = 0;
    GLuint mask = 0;

    float specular_intensity = 5;
    float specular_exponent = 100;

    Material();
    Material(std::string name);
};
#endif
