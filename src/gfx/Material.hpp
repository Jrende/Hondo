#ifndef __HONDO_MATERIAL_H__
#define __HONDO_MATERIAL_H__
class Material;
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
class Material {
  private:
  public:
    std::string name;
    GLuint diffuse_map;
    GLuint specular_map;
    GLuint normal_map;
    Material();
    Material(std::string name);
};
#endif
