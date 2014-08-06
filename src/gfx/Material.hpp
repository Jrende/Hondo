gifndef __HONDO_MATERIAL_H__
#define __HONDO_MATERIAL_H__
class Material;
#include <glm/glm.hpp>
#include <SOIL.h>
#include <GL/glew.h>
class Material {
  private:
    GLUint diffuse_texture;
  public:
    Material();
};
#endif
