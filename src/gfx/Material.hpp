#ifndef __HONDO_MATERIAL_H__
#define __HONDO_MATERIAL_H__
class Material;
#include <string>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <GL/glew.h>
class Material {
  private:
  public:
    std::string name;

    GLuint diffuse_map;
    GLuint specular_map;
    GLuint normal_map;

    float specular_intensity;
    float specular_exponent;

    Material();
    Material(std::string name);
};
#endif