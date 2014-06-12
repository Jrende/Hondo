#ifndef __HONDO_RENDEROBJECT_H__
#define __HONDO_RENDEROBJECT_H__
class RenderObject;
#include <string>
#include "RenderObject.h"
#include "VertexArray.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
class RenderObject {
  private:
    const std::shared_ptr<VertexArray> vArray;
  public:
    glm::mat4 modelMatrix;
    RenderObject(std::shared_ptr<VertexArray> vArray);
    void render();
    void translate(const glm::vec3& pos);
};
#endif
